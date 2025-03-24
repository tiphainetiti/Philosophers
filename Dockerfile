# Utiliser une image officielle d'Ubuntu comme image de base
FROM ubuntu:latest

# Mettre à jour le dépôt de paquets et installer Valgrind et GCC
RUN apt-get update && apt-get install -y valgrind gcc

# Définir le répertoire de travail
WORKDIR /usr/src/app

# Copier le contenu du répertoire actuel dans le conteneur à /usr/src/app
COPY . .

# Compiler le fichier source avec les flags spécifiés
RUN gcc -Wall -Wextra -Werror -pthread -g -o philo srcs/main.c srcs/init.c srcs/utils.c

# Définir le point d'entrée pour exécuter Valgrind avec l'outil Helgrind
ENTRYPOINT ["valgrind", "--tool=helgrind", "./philo"]

# Définir CMD pour permettre le passage des arguments
CMD ["4", "800", "200", "200", "5"]