COMMIT = $(shell git log -1 --format=%h)

docker:
	docker build . -t \
	simfection/simfection:$(COMMIT) \
	 --build-arg COMMIT=$(COMMIT)

devdocker:
	docker build -f dev.Dockerfile . -t \
	simfection/simfection_dev:$(COMMIT) \

pushdocker:
	docker push simfection/simfection:$(COMMIT)
	#GITHUB_PAT_ = $(shell echo ${GITHUB_PAT})

debugdocker:
	cp requirements.txt docker/ && \
	docker build -f docker/debug.Dockerfile . -t \
	simfection/simfection_debug:$(COMMIT) \
	--build-arg COMMIT=$(COMMIT) && \
	rm docker/requirements.txt

pushdebugdocker:
	docker push simfection/simfection_debug:$(COMMIT)
