#include <rtv1.h>

void	debug_ray(t_obj *obj, t_ray ray, t_vector3 color)
{
	print_vector3f(ray.origin, "Cam:");
	print_vector3f(ray.dir, "\nRay:");
	printf("\nDistance:\t%f\n", obj->distance);
	print_vector3f(color, "Color:");
}

void	print_vector3f(t_vector3 vector, char *comment)
{
	printf("%s\t", comment);
	printf("X %f\t", vector.x);
	printf("Y %f\t", vector.y);
	printf("Z %f\t", vector.z);
}

void	print_vector3(t_vector3	vector, char *comment)
{
	printf("%s\t", comment);
	printf("X %d\t", (int)vector.x);
	printf("Y %d\t", (int)vector.y);
	printf("Z %d\t", (int)vector.z);
}

void	print_vector2(t_vector2	vector, char *comment)
{
	printf("%s\t", comment);
	printf("X %d\t", (int)vector.x);
	printf("Y %d\t", (int)vector.y);
}
