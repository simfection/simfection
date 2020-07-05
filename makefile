COMMIT = $(shell git log -1 --format=%h)

debugdocker:
	docker build -f docker/debug.Dockerfile . -t \
	simfection/simfection_debug:$(COMMIT) \
	--build-arg COMMIT=$(COMMIT)

pushdebugdocker:
	docker push simfection/simfection_debug:$(COMMIT)
