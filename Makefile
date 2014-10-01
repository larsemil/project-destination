SERVER_DIR = server
CLIENT_DIR = client

.PHONY: all
all: server client

.PHONY: server
server:
	$(MAKE) -C $(SERVER_DIR)

.PHONY: client
client:
	$(MAKE) -C $(CLIENT_DIR)

.PHONY: clean
clean:
	@rm -r $(SERVER_DIR)/obj
	@rm -r $(CLIENT_DIR)/obj
