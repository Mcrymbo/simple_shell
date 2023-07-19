#include "shell.h"

/**
 * _memcpy - copies information between void pointers
 * @des: destination pointer
 * @src: soirce pointer
 * @size: size of dest pointer
 */
void _memcpy(void *dest, const void *src, unsigned int size)
{
	char *dst = (char *)dest;
	char *src_ptr = (char *)src;
	unsigned int i;

	for (i = 0; i < size; i++)
		dst[i] = src_ptr[i];
}
/**
 * _realloc - reallocates memory
 * @ptr: memory previousely allocated
 * @old_size: size of the preveousely allocated memory
 * @new_size: size of new memory
 * Return: no return
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);
	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);
	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);
	free(ptr);
	return (newptr);
}
/**
 * _reallocdp - reallocates memory of a double pointers
 *  @ptr: double pointer to preveousely allocated memory
 *  @old_size: size in bytes of previouely allocated ptr
 *  @new_size: size in bytes of new memory block
 *  Return: pointer to reallocated memory
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));
	if (new_size == old_size)
		return (ptr);
	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);
	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];
	free(ptr);
	return (newptr);
}
