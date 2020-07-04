COMMIT := $(shell git log -1 --format=%h)

docker:
	docker build . -t \
	simfection/simfection:$(COMMIT) \
	 --build-arg COMMIT=$(COMMIT)

devdocker:
	docker build -f dev.Dockerfile . -t \
	simfection/simfection_dev:$(COMMIT) \

pushdocker:
	docker push simfection/simfection:$(COMMIT)

	OMMIT := $(shell git log -1 --format=%h)
	#GITHUB_PAT_ = $(shell echo ${GITHUB_PAT})

debugdocker:
	docker build -f debug.Dockerfile . -t \
	simfection/simfection_debug:$(COMMIT) \
	--build-arg COMMIT=$(COMMIT)
