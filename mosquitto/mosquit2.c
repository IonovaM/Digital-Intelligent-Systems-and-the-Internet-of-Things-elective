#include "mosquitto2.h"
#include "mosquitto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



#include <math.h>
#define PI 3.14159265358979323846f
#define SAMPLE_RATE 44100    // Adjust this to change the frequency of the resulting sine wave
#define FREQ 1000            // Adjust this to change the frequency of the sine wave
#define MAX_AMPLITUDE 40.0f  // Adjust this to change the maximum value of the sine wave
#define MIN_AMPLITUDE 10.0f  // Adjust this to change the minimum value of the sine wave


/* Callback called when the client receives a CONNACK message from the broker. */
void on_connect(struct mosquitto *mosq, void *obj, int reason_code)
{
    /* Print out the connection result. mosquitto_connack_string() produces an
     * appropriate string for MQTT v3.x clients, the equivalent for MQTT v5.0
     * clients is mosquitto_reason_string().
     */
    printf("on_connect: %s\n", mosquitto_connack_string(reason_code));
    if(reason_code != 0){
        /* If the connection fails for any reason, we don't want to keep on
         * retrying in this example, so disconnect. Without this, the client
         * will attempt to reconnect. */
        mosquitto_disconnect(mosq);
    }

    /* You may wish to set a flag here to indicate to your application that the
     * client is now connected. */
}


/* Callback called when the client knows to the best of its abilities that a
 * PUBLISH has been successfully sent. For QoS 0 this means the message has
 * been completely written to the operating system. For QoS 1 this means we
 * have received a PUBACK from the broker. For QoS 2 this means we have
 * received a PUBCOMP from the broker. */
void on_publish(struct mosquitto *mosq, void *obj, int mid)
{
    printf("Message with mid %d has been published.\n", mid);
}


int get_temperature(void)
{
    static int count = 0;
    const int m[60] = {100, 99, 98, 97, 95, 93, 90, 87, 83, 79, 75, 70, 65, 60, 55, 49, 44, 39, 34, 29, 24, 20, 16, 12, 9, 6, 4, 2, 1, 0, 0, 0, 1, 2, 4, 6, 9, 12, 16, 20, 25, 29, 34, 39, 44, 50, 55, 60, 65, 70, 74, 79, 83, 87, 90, 93, 95, 97, 98, 99};
    //sleep(1); /* Prevent a storm of messages - this pretend sensor works at 1Hz */

    sleep(1);
    if (count >= 60) {
        count = 0;
    }
    return m[count++];
}


/*void loop(){
for (int i=0;i<256;i++) {
  Serial.print(byte(127+(127*sin(PI*i*0.007843))));
  Serial.print(", ");
}
delay(10000); // Задержка, чтобы успеть скопировать :)
}
*/

/* This function pretends to read some data from a sensor and publish it.*/
void publish_sensor_data(struct mosquitto *mosq)
{
    char payload[20];
    int temp;
    int rc;

    /* Get our pretend data */
    temp = get_temperature();
    /* Print it to a string for easy human reading - payload format is highly
     * application dependent. */
    snprintf(payload, sizeof(payload), "%d", temp);

    /* Publish the message
     * mosq - our client instance
     * *mid = NULL - we don't want to know what the message id for this message is
     * topic = "example/temperature" - the topic on which this message will be published
     * payloadlen = strlen(payload) - the length of our payload in bytes
     * payload - the actual payload
     * qos = 2 - publish with QoS 2 for this example
     * retain = false - do not use the retained message feature for this message
     */
    rc = mosquitto_publish(mosq, NULL, "example/humidity", strlen(payload), payload, 2, false);
    if(rc != MOSQ_ERR_SUCCESS){
        fprintf(stderr, "Error publishing: %s\n", mosquitto_strerror(rc));
    }
}


int main(int argc, char *argv[])
{
    struct mosquitto *mosq;
    int rc;

    /* Required before calling other mosquitto functions */
    mosquitto_lib_init();

    /* Create a new client instance.
     * id = NULL -> ask the broker to generate a client id for us
     * clean session = true -> the broker should remove old sessions when we connect
     * obj = NULL -> we aren't passing any of our private data for callbacks
     */
    mosq = mosquitto_new(NULL, true, NULL);
    if(mosq == NULL){
        fprintf(stderr, "Error: Out of memory.\n");
        return 1;
    }

    /* Configure callbacks. This should be done before connecting ideally. */
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_publish_callback_set(mosq, on_publish);

    /* Connect to test.mosquitto.org on port 1883, with a keepalive of 60 seconds.
     * This call makes the socket connection only, it does not complete the MQTT
     * CONNECT/CONNACK flow, you should use mosquitto_loop_start() or
     * mosquitto_loop_forever() for processing net traffic. */
    rc = mosquitto_connect(mosq, "test.mosquitto.org", 1883, 60);
    if(rc != MOSQ_ERR_SUCCESS){
        mosquitto_destroy(mosq);
        fprintf(stderr, "Error: %s\n", mosquitto_strerror(rc));
        return 1;
    }

    /* Run the network loop in a background thread, this call returns quickly. */
    rc = mosquitto_loop_start(mosq);
    if(rc != MOSQ_ERR_SUCCESS){
        mosquitto_destroy(mosq);
        fprintf(stderr, "Error: %s\n", mosquitto_strerror(rc));
        return 1;
    }

    /* At this point the client is connected to the network socket, but may not
     * have completed CONNECT/CONNACK.
     * It is fairly safe to start queuing messages at this point, but if you
     * want to be really sure you should wait until after a successful call to
     * the connect callback.
     * In this case we know it is 1 second before we start publishing.
     */
    while(1){
        publish_sensor_data(mosq);
    }

    mosquitto_lib_cleanup();
    return 0;
}
