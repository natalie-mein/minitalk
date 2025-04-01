# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/02 15:37:16 by nmeintje          #+#    #+#              #
#    Updated: 2024/10/02 15:37:18 by nmeintje         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

CFLAGS = -Wall -Wextra -Werror
CC = cc

HEADER = minitalk.h 
HEADER_BONUS = minitalk_bonus.h 

LIBFT_DIR = ./libft
LIBFT_FLAGS = -L $(LIBFT_DIR) -lft

OBJS_SERVER = server.o
OBJS_CLIENT = client.o
OBJS_SERVER_BONUS = server_bonus.o
OBJS_CLIENT_BONUS = client_bonus.o
LIBFT = $(LIBFT_DIR)/libft.a

all: createlibft $(SERVER) $(CLIENT)

bonus: createlibft $(SERVER_BONUS) $(CLIENT_BONUS)

# Compile all libft source files to object files
createlibft:
		@echo "Building libft..."
		@make -C $(LIBFT_DIR)

# Compiling the server executable
$(SERVER): $(OBJS_SERVER) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFT_FLAGS) -o $(SERVER)
	@echo "Compiled $(SERVER) successfully!"

# Compiling the client executable
$(CLIENT): $(OBJS_CLIENT) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBFT_FLAGS) -o $(CLIENT)
	@echo "Compiled $(CLIENT) successfully!"

# Compiling the bonus server executable
$(SERVER_BONUS): $(OBJS_SERVER_BONUS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_SERVER_BONUS) $(LIBFT_FLAGS) -o $(SERVER_BONUS)
	@echo "Compiled $(SERVER_BONUS) successfully!"

# Compiling the bonus client executable
$(CLIENT_BONUS): $(OBJS_CLIENT_BONUS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_CLIENT_BONUS) $(LIBFT_FLAGS) -o $(CLIENT_BONUS)
	@echo "Compiled $(CLIENT_BONUS) successfully!"

# Compiling server.c to server.o
server.o: server.c $(HEADER)
	@$(CC) $(CFLAGS) -c server.c -o server.o
	@echo "Compiled server.o successfully!"

# Compiling client.c to client.o
client.o: client.c $(HEADER)
	@$(CC) $(CFLAGS) -c client.c -o client.o
	@echo "Compiled client.o successfully!"

# Compiling server_bonus.c to server_bonus.o
server_bonus.o: server_bonus.c $(HEADER_BONUS)
	@$(CC) $(CFLAGS) -c server_bonus.c -o server_bonus.o
	@echo "Compiled server_bonus.o successfully!"

# Compiling client_bonus.c to client_bonus.o
client_bonus.o: client_bonus.c $(HEADER_BONUS)
	@$(CC) $(CFLAGS) -c client_bonus.c -o client_bonus.o
	@echo "Compiled client_bonus.o successfully!"

# Clean up object files
clean:
	rm -f *.o
	rm -f $(LIBFT_DIR)/*.o
	
# Full clean
fclean: clean
	rm -f $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)
	rm -f $(LIBFT_DIR)/libft.a

# Rebuild everything
re: fclean all

.PHONY: all bonus clean fclean re
