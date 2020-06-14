COMMIT := $(shell git log -1 --format=%h)

docker:
	docker build . -t \
	simfection/simfection:$(COMMIT) \
	 --build-arg COMMIT=$(COMMIT)

devdocker:
	docker build -f dev.Dockerfile . -t \
	simfection/simfection:$(COMMIT) \

pushdocker:
	docker push simfection/simfection:$(COMMIT)
