/*
 * orb_manager.c
 *
 *  Created on: May 16, 2018
 *      Author: lidq
 */

#include <orb_manager.h>

sem_t sem_rw;

int orb_main(int argc, char *argv[])
{
	sem_init(&sem_rw, 0, 1);
}

orb_advert_t orb_advertise(const struct orb_metadata *meta)
{
	if (meta == NULL)
	{
		printf("[orb] %s meta is null.\n", __func__);
		return NULL;
	}

	char path[ORB_SIZE_NAME];
	snprintf(path, ORB_SIZE_NAME, "%s/%s", ORB_PATH_BASE, meta->o_name);

	//printf("[orb] %s\n", meta->o_name);
	s_orb_sub *sub = malloc(sizeof(s_orb_sub));
	s_orb_pub *pub = malloc(sizeof(s_orb_pub));

	pub->meta = malloc(sizeof(meta->o_size));

	sem_wait(&sem_rw);

	int fd = open(path, O_CREAT | O_WRONLY, 0666);

	sem_init(&pub->sem_rw, 0, 1);
	sub->pub = pub;
	memset(pub->sub_updated, 0, ORB_SUB_MAX_NUM);
	lseek(fd, 0, SEEK_SET);
	write(fd, &sub, sizeof(void*));
	close(fd);

	sem_post(&sem_rw);

	orb_advert_t orb_adv = (orb_advert_t) sub;
	return orb_adv;
}

int orb_unadvertise(orb_advert_t orb_adv)
{
	s_orb_sub *sub = (s_orb_sub *) orb_adv;
	if (sub == NULL || sub->pub == NULL || sub->pub->meta == NULL)
	{
		return -1;
	}
	sem_destroy(&sub->pub->sem_rw);
	free(sub->pub->meta);
	free(sub->pub);
	free(sub);
}

int orb_publish(const struct orb_metadata *meta, orb_advert_t orb_adv, void *data)
{
	if (meta == NULL)
	{
		printf("[orb] %s meta is null.\n", __func__);
		return -1;
	}

	s_orb_sub *sub = (s_orb_sub *) orb_adv;

	if (sub == NULL || sub->pub == NULL)
	{
		printf("[orb] %s pub is null.\n", __func__);
		return -1;
	}

	if (data == NULL)
	{
		printf("[orb] %s data is null.\n", __func__);
		return -1;
	}

	s_orb_pub *pub = sub->pub;

	sem_wait(&pub->sem_rw);

	memset(pub->sub_updated, 1, ORB_SUB_MAX_NUM);
	memcpy(pub->meta, data, meta->o_size);

	sem_post(&pub->sem_rw);

	return 0;
}

orb_advert_t orb_subscribe(const struct orb_metadata *meta)
{
	if (meta == NULL)
	{
		printf("[orb] %s meta is null.\n", __func__);
		return NULL;
	}

	char path[ORB_SIZE_NAME];
	snprintf(path, ORB_SIZE_NAME, "%s/%s", ORB_PATH_BASE, meta->o_name);

	s_orb_sub *sub = malloc(sizeof(s_orb_sub));

	sem_wait(&sem_rw);

	sub->fd = open(path, O_CREAT | O_RDONLY, 0666);
	s_orb_sub *pub_sub = NULL;
	lseek(sub->fd, 0, SEEK_SET);
	read(sub->fd, &pub_sub, sizeof(void*));

	sem_post(&sem_rw);

	sub->pub = pub_sub->pub;
	orb_advert_t orb_adv = (orb_advert_t) sub;
	return orb_adv;
}

int orb_unsubscribe(orb_advert_t orb_adv)
{
	s_orb_sub *sub = (s_orb_sub *) orb_adv;
	if (sub == NULL)
	{
		return -1;
	}
	if (sub->fd > -1)
	{
		close(sub->fd);
	}
	free(sub);
}

int orb_check(orb_advert_t orb_adv, bool *updated)
{
	s_orb_sub *sub = (s_orb_sub *) orb_adv;
	if (sub == NULL || sub->pub == NULL)
	{
		printf("[orb] %s sub is null.\n", __func__);
		return -1;
	}

	if (updated == NULL)
	{
		printf("[orb] %s updated is null.\n", __func__);
		return -1;
	}

	*updated = false;

	s_orb_pub *pub = sub->pub;

	sem_wait(&pub->sem_rw);

	if (pub->sub_updated[sub->fd])
	{
		*updated = true;
	}

	sem_post(&pub->sem_rw);

	return 0;
}

int orb_copy(const struct orb_metadata *meta, orb_advert_t orb_adv, void *data)
{
	s_orb_sub *sub = (s_orb_sub *) orb_adv;
	if (sub == NULL || sub->pub == NULL)
	{
		printf("[orb] %s sub is null.\n", __func__);
		return -1;
	}

	if (meta == NULL)
	{
		printf("[orb] %s meta is null.\n", __func__);
		return -1;
	}

	if (sub->fd < 0)
	{
		printf("[orb] %s fd is %d.\n", __func__, sub->fd);
		return -1;
	}

	if (data == NULL)
	{
		printf("[orb] %s data is null.\n", __func__);
		return -1;
	}

	s_orb_pub *pub = sub->pub;

	sem_wait(&pub->sem_rw);

	memcpy(data, pub->meta, sizeof(meta->o_size));
	pub->sub_updated[sub->fd] = 0;

	sem_post(&pub->sem_rw);

	return 0;
}
