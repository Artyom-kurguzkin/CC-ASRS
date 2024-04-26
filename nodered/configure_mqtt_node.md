
Set up HiveMQ Cloud mqtt broker (it is free at least at this point). You will need to save URL and access credentials.

Get HiveMQ TLS client certificate from here: https://community.hivemq.com/t/frequently-asked-questions-hivemq-cloud/514 

Both robot and nodered endpoints use it to communicate with the broker over TLS.

I defined mqtt 'topic' in our Publisher's code (robot). It is  `testTopic`.

In nodered's mqtt-in node there is a page for configureing `Server`, nxt changes are done there

<br>

