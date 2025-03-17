# Utiliser une image officielle d'Ubuntu comme image de base
FROM ubuntu:latest

# Mettre à jour le dépôt de paquets et installer Valgrind et GCC
RUN apt-get update && apt-get install -y valgrind gcc

# Définir le répertoire de travail
WORKDIR /usr/src/app

# Copier le contenu du répertoire actuel dans le conteneur à /usr/src/app
COPY . .

# Compiler le fichier source avec les flags spécifiés
RUN gcc -Wall -Wextra -Werror -pthread -o src/a.out src/main.c

# Exécuter Valgrind avec l'outil Helgrind par défaut
CMD ["valgrind", "--tool=helgrind", "src/a.out"]