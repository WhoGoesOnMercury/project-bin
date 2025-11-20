# Only use this file if you can run Makefiles through the `make` utility. 
# Otherwise, just copy the commands here to setup the application

# Variables for Makefile
PROTO_DIR = proto
PB_DIR = proto
PROTO_FILE = media.proto

CONSUMER_DIR = consumer
PRODUCER_DIR = producer

all: build

# gRPC build with protoc (for Go)
proto:
	cd proto
	@echo "Generating gRPC code using protoc..."
	protoc --go_out=. --go_opt=paths=source_relative --go-grpc_out=. --go-grpc_opt=paths=source_relative $(PROTO_FILE)

build:
	@echo "Building Docker images..."
	docker-compose build

up: 
	@echo "Setting up Docker containers..."
	docker-compose up

down:
	@echo "Tearing containers down..."
	docker-compose down -v --remove-orphans

restart:
	@echo "Restarting Producer-Consumer service..."
	docker-compose down
	docker-compose up --build

clean:
	@echo "Cleaning received_videos folder"
	del /Q received_videos\*.mp4

# In case files have the same names as commands
.PHONY: all proto build up down restart clean
