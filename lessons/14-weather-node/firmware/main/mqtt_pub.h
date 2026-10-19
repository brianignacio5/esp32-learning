#pragma once

/* Start the MQTT client. Waits up to 15 seconds for a connection.
   A missing broker is logged and is not fatal. */
void mqtt_start(void);

/* Publish json to sensors/weather/reading. Returns 0 when the client accepts it. */
int mqtt_publish_json(const char *json);
