const AWS = require('aws-sdk');
const mqtt = require('mqtt');

const iotEndpoint = 'your-iot-endpoint';
const iotPort = 8883;
const iotRegion = 'your-iot-region';
const iotAccessKeyId = 'your-iot-access-key-id';
const iotSecretAccessKey = 'your-iot-secret-access-key';
const mqttTopic = 'username/feeds/light-control';

const mqttClient = mqtt.connect({
    host: iotEndpoint,
    port: iotPort,
    region: iotRegion,
    accessKeyId: iotAccessKeyId,
    secretAccessKey: iotSecretAccessKey,
    protocol: 'mqtts'
});

exports.handler = function(event, context, callback) {
    const request = event.request;
    const session = event.session;
    
    if (request.type === 'IntentRequest' && request.intent.name === 'LightControlIntent') {
        const state = request.intent.slots.State.value;
        let payload = 0;
        
        if (state === 'on') {
            payload = 1;
        }
        
        mqttClient.publish(mqttTopic, payload.toString(), function(err) {
            if (err) {
                console.log(err);
                callback(err);
            } else {
                callback(null, {
                    version: '1.0',
                    response: {
                        outputSpeech: {
                            type: 'PlainText',
                            text: 'The lights are now ' + state
                        }
                    }
                });
            }
        });
    }
};

//Replace the placeholders with your own values, such as your Adafruit IO username and key, your AWS IoT endpoint, and your AWS access key ID and secret access key.