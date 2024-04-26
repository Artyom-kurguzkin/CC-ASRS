First make sure you completed steps listed in steps_to_configure_gke.md . If you running nodred somehow differently, look elsewhere for possible firewall isues. 

<br>

Set up HiveMQ Cloud mqtt broker (it is free at least at this point). You will need to save URL and access credentials.

Get HiveMQ TLS client certificate from here: https://community.hivemq.com/t/frequently-asked-questions-hivemq-cloud/514 

Both robot and nodered endpoints use it to communicate with the broker over TLS.

<br>

I defined mqtt 'topic' in our Publisher's code (robot). It is  `testTopic`.

In nodered's mqtt-in node there is a page for configureing `Server`, next changes are done there

<br>

![mqttGuide1](https://github.com/Artyom-kurguzkin/CC-ASRS/assets/10873919/1e2810cd-2782-406e-b330-6c99ba09a9f6)

<br>

Next, paste the URL you've got from HiveMQ and tick `Use TLS`. Here is my HiveMQ link, but after June 2024 it won't be operational. 

* 06ea4fbd57d348d0931b9543624acafa.s1.eu.hivemq.cloud

<br>

In the Security tab add you access credentials for the mqtt conversation. Same jazz as with the HiveMQ link:

* kurg0002 : 9y83jy89L
* for better security consider using something that will handle credentials for you like Azure key vault.

<br>

In the TLS properties ONLY add CA Certificate that you downloaded earlier. Tick verify certificate. 

![mqttGuide2](https://github.com/Artyom-kurguzkin/CC-ASRS/assets/10873919/967eedaa-4b65-4e33-8fce-747f81ec693e)


Click deploy, You should be receiving messages now. 
