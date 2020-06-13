COMMIT := $(shell git log -1 --format=%h)

docker:
	docker build . -t \
	simfection:$(COMMIT) \

pushdocker:
	docker push AWSID.dkr.ecr.us-east-1.amazonaws.com/simfection:$(COMMIT)

