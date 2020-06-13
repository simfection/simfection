COMMIT := $(shell git log -1 --format=%h)
#GITHUB_PAT_ = $(shell echo ${GITHUB_PAT})

docker:
	docker build . -t \
	sinfection:$(COMMIT) \

pushdocker:
	docker push 094953151259.dkr.ecr.us-east-1.amazonaws.com/tfpopsyyn:$(COMMIT)

twostagedocker:
	docker build . -t \
	094953151259.dkr.ecr.us-east-1.amazonaws.com/tfpopsyn:$(COMMIT) \
	--build-arg GITHUB_PAT=$(GITHUB_PAT) --build-arg COMMIT=$(COMMIT)
