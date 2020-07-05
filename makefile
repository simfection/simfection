COMMIT = $(shell git log -1 --format=%h)

debugdocker:
	cp requirements.txt docker/ && \
	docker build -f docker/debug.Dockerfile . -t \
	simfection/simfection_debug:$(COMMIT) \
	--build-arg COMMIT=$(COMMIT) && \
	rm docker/requirements.txt

pushdebugdocker:
	docker push simfection/simfection_debug:$(COMMIT)
