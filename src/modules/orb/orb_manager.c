/*
 * orb_manager.c
 *
 *  Created on: May 16, 2018
 *      Author: lidq
 */

#include <orb_manager.h>

static sem_t sem_rw;

int orb_main(int argc, char *argv[])
{
	sem_init(&sem_rw, 0, 1);
}

int orb_advertise(const struct orb_metadata *meta)
{
	if (meta == NULL)
	{
		printf("[orb] %s meta is null.\n", __func__);
		return -1;
	}

	//printf("[orb] %s\n", meta->o_name);

	char path[ORB_SIZE_NAME];
	snprintf(path, ORB_SIZE_NAME, "%s/%s", ORB_PATH_BASE, meta->o_name);
	int fd = open(path, O_CREAT | O_WRONLY, 0666);
	if (fd < 0)
	{
		printf("[orb] %s can not create orb node file %s.\n", __func__, path);
		return -1;
	}

	char orb_sub_updated[ORB_SUB_MAX_NUM];
	memset(orb_sub_updated, false, ORB_SUB_MAX_NUM);

	char buff[meta->o_size];
	memset(buff, 0, meta->o_size);

	sem_wait(&sem_rw);

	lseek(fd, 0, SEEK_SET);
	write(fd, &fd, sizeof(int));
	write(fd, orb_sub_updated, ORB_SUB_MAX_NUM);
	write(fd, buff, meta->o_size);
	fsync(fd);

	sem_post(&sem_rw);

	return fd;
}

int orb_unadvertise(int fd)
{
	if (fd < 0)
	{
		printf("[orb] %s fd is %d.\n", __func__, fd);
		return -1;
	}
	return close(fd);
}

int orb_publish(const struct orb_metadata *meta, int fd, void *data)
{
	if (meta == NULL)
	{
		printf("[orb] %s meta is null.\n", __func__);
		return -1;
	}

	if (fd < 0)
	{
		printf("[orb] %s fd is invaild.\n", __func__);
		return -1;
	}

	if (data == NULL)
	{
		printf("[orb] %s data is null.\n", __func__);
		return -1;
	}

	char orb_sub_updated[ORB_SUB_MAX_NUM];
	memset(orb_sub_updated, true, ORB_SUB_MAX_NUM);

	sem_wait(&sem_rw);

	lseek(fd, sizeof(fd), SEEK_SET);
	write(fd, orb_sub_updated, ORB_SUB_MAX_NUM);
	write(fd, data, meta->o_size);
	fsync(fd);

	sem_post(&sem_rw);

	return 0;
}

int orb_subscribe(const struct orb_metadata *meta)
{
	if (meta == NULL)
	{
		printf("[orb] %s meta is null.\n", __func__);
		return -1;
	}

	char path[ORB_SIZE_NAME];
	snprintf(path, ORB_SIZE_NAME, "%s/%s", ORB_PATH_BASE, meta->o_name);

	int fd = open(path, O_CREAT | O_RDWR, 0666);
	if (fd < 0)
	{
		printf("[orb] %s can not open orb node file %s.\n", __func__, path);
		return -1;
	}

	return fd;
}

int orb_unsubscribe(int fd)
{
	if (fd < 0)
	{
		printf("[orb] %s fd is %d.\n", __func__, fd);
		return -1;
	}
	return close(fd);
}

int orb_check(int fd, bool *updated)
{
	if (fd < 0)
	{
		printf("[orb] %s fd is %d.\n", __func__, fd);
		return -1;
	}

	if (updated == NULL)
	{
		printf("[orb] %s updated is null.\n", __func__);
		return -1;
	}

	*updated = false;

	char orb_sub_updated[ORB_SUB_MAX_NUM];

	sem_wait(&sem_rw);

	lseek(fd, sizeof(fd), SEEK_SET);
	int len = read(fd, &orb_sub_updated, ORB_SUB_MAX_NUM);

	sem_post(&sem_rw);

	if (orb_sub_updated[fd])
	{
		*updated = true;
	}

	return 0;
}

int orb_copy(const struct orb_metadata *meta, int fd, void *data)
{
	if (meta == NULL)
	{
		printf("[orb] %s meta is null.\n", __func__);
		return -1;
	}

	if (fd < 0)
	{
		printf("[orb] %s fd is %d.\n", __func__, fd);
		return -1;
	}

	if (data == NULL)
	{
		printf("[orb] %s data is null.\n", __func__);
		return -1;
	}

	char orb_sub_updated[ORB_SUB_MAX_NUM];

	sem_wait(&sem_rw);

	lseek(fd, sizeof(fd), SEEK_SET);
	read(fd, &orb_sub_updated, ORB_SUB_MAX_NUM);
	orb_sub_updated[fd] = false;
	read(fd, data, meta->o_size);
	lseek(fd, sizeof(fd), SEEK_SET);
	write(fd, orb_sub_updated, ORB_SUB_MAX_NUM);

	sem_post(&sem_rw);

	return 0;
}
