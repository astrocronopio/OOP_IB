#include <iostream>
#include <stdlib.h>


#include "mqtt.hpp"
#include "mqtt_errors.hpp"
#include "mqtt_message.hpp"
#include "mqtt_broker.hpp"
#include "mqtt_client.h"


int main(int argc, char* argv[])
{
	std::cout << "Inicializando broker" << std::endl;

	broker main_broker;

	std::cout << "Inicializando clientes" << std::endl;
	short CLIENT_ID_1=1;
	client client_1(&main_broker, CLIENT_ID_1);

	user_callback cb;
	client.set_callback(cb);

	mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(true);
	std::cout << "...OK" << std::endl;

	try {
		std::cout << "\nConnecting..." << std::endl;
		client.connect(connOpts);
		std::cout << "...OK" << std::endl;

		// First use a message pointer.

		std::cout << "\nSending message..." << std::endl;
		auto pubmsg = mqtt::make_message(TOPIC, PAYLOAD1);
		pubmsg->set_qos(QOS);
		client.publish(pubmsg);
		std::cout << "...OK" << std::endl;

		// Now try with itemized publish.

		std::cout << "\nSending next message..." << std::endl;
		client.publish(TOPIC, PAYLOAD2, strlen(PAYLOAD2)+1);
		std::cout << "...OK" << std::endl;

		// Now try with a listener, no token, and non-heap message

		std::cout << "\nSending final message..." << std::endl;
		client.publish(mqtt::message(TOPIC, PAYLOAD3, QOS, false));
		std::cout << "OK" << std::endl;

		// Disconnect
		std::cout << "\nDisconnecting..." << std::endl;
		client.disconnect();
		std::cout << "...OK" << std::endl;
	}
	catch (const mqtt::persistence_exception& exc) {
		std::cerr << "Persistence Error: " << exc.what() << " ["
			<< exc.get_reason_code() << "]" << std::endl;
		return 1;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << exc.what() << std::endl;
		return 1;
	}

	std::cout << "\nExiting" << std::endl;
 	return 0;
}

