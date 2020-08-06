#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
void find_name(char *name);

int main (int argc, char **argv)
{
        if (argc != 2)
        {
                printf("Error: el numero de argumentos son incorrectos\n");
                exit(97);
        }
        find_name(argv[1]);
        return (0);
}

void find_name(char *name)
{
        int fd,leer = 1, nlength = 0, ps = 1, repeat = 0;
        int i, j;
        char buffer[1024];

        fd = open("/home/vagrant/CodingChallangeinC/names", O_RDONLY);
        if (fd == -1)
                exit(98);
        while (name[nlength])
                nlength++;
        while (leer > 0)
        {
                leer = read(fd, buffer, 1024);
                if (leer == -1)
                        exit(99);
                for (i = 0; i < leer; i++)
                {
                        if (buffer[i] != '\n')
                        {
                                for (j = 0; buffer[i] == name[j]; i++, j++)
                                {
                                        if (nlength - 1 == j)
                                        {
                                                repeat++;
                                                printf("Se encontro el nombre %s, en la posicion %d\n", name, ps);
                                        }
                                }
                                while (buffer[i + 1] != '\n')
                                {
                                        i++;
                                }
                        }
                        else
                        {
                                ps++;
                        }
                }
        }
        if (repeat > 0)
                printf("El nombre se encontro en %d ocasion(es)\n", repeat);
        else
                printf("No se encontro el nombre en la lista\n");
        close(fd);
}
