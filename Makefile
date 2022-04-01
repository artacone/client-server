CLIENT		=	client.out

SERVER		=	server.out

CLIENT_DIR	=	./client/

SERVER_DIR	=	./server/

RM			=	rm -f


all: $(CLIENT) $(SERVER)

$(CLIENT):
	@echo "Building client..."
	@make -C $(CLIENT_DIR)
	@echo "Done!"
	@mv $(CLIENT_DIR)client $(CLIENT)

$(SERVER):
	@echo "Building server..."
	@make -C $(SERVER_DIR)
	@echo "Done!"
	@mv $(SERVER_DIR)server $(SERVER)

clean:
	@echo "Cleaning client..."
	@make -C $(CLIENT_DIR) clean
	@echo "Cleaning server..."
	@make -C $(SERVER_DIR) clean
	@echo "Done!"

fclean: clean
	@echo "Fully cleaning client..."
	@make -C $(CLIENT_DIR) fclean
	@echo "Fully cleaning server..."
	@make -C $(SERVER_DIR) fclean
	$(RM) $(CLIENT) $(SERVER)
	@echo "Done!"

re: fclean all

.PHONY: all clean fclean re
