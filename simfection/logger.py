import logging
import logging.config
import yaml


class SimfectionLogger:
    def __init__(self, name=None):
        # Config and init logger
        # with open('logger.yaml', 'rt') as f:
        #    config = yaml.safe_load(f.read())
        config = {
            'version': 1,
            'disable_existing_loggers': False,
            'formatters': {'console': {'format': '%(asctime)s  %(name)-30s  %(levelname)s  %(message)s'},
                           'file': {'format': '%(asctime)s %(name)-12s %(levelname)-8s %(message)s'}},
            'handlers': {'console': {'class': 'logging.StreamHandler',
                                     'level': 'INFO',
                                     'formatter': 'console',
                                     'stream': 'ext://sys.stdout'},
                         'file': {'class': 'logging.FileHandler',
                                  'level': 'DEBUG',
                                  'formatter': 'file',
                                  'filename': 'simfection.log',
                                  'encoding': 'utf8'}},
            'root': {'level': 'NOTSET',
                     'handlers': ['console', 'file'],
                     'propagate': True},
            'loggers': {'file': {'handlers': ['file']}}
        }
        logging.config.dictConfig(config)
        if name == '__main__':
            logger = logging.getLogger('simfection')
        else:
            logger = logging.getLogger(name)
        logger.setLevel(logging.DEBUG)
        self.logger = logger

    def get_logger(self):
        return self.logger
