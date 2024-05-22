# How top onfigure  connection with mongodb Atlas

---

<br>

Create a document in the database, like this: 

![image](https://github.com/Artyom-kurguzkin/CC-ASRS/assets/10873919/2a0d5263-2d15-46a4-93c1-53fe64ca9a0c)

HERE is the approximate schema

```
_id
_level : "High" or "LOW"
_name "Phentanyl" or "Panadol"
_location: "15, 3"
  
```


<br>

## mongodb Atlas security settings

Allow access from anywhere

![image](https://github.com/Artyom-kurguzkin/CC-ASRS/assets/10873919/021c358e-8f3f-415f-b65c-213e08766076)

<br>

Create a new account to access the database

![image](https://github.com/Artyom-kurguzkin/CC-ASRS/assets/10873919/36ffbdb1-4118-43d0-aa5e-927792b5d2a5)

<br>

Now, you should be able to construct a data connection string. here is mine:

```
mongodb+srv://Nodered:LQmpKU4C0DX9cVay@cluster0.1cnydcd.mongodb.net
```

<br>

---

## configure Nodred

### mongodb node

Install this module: `node-red-contrib-mongodb-aleph`

<br>

Select the collection and operation

![image](https://github.com/Artyom-kurguzkin/CC-ASRS/assets/10873919/2273f18b-03c6-4a30-947a-86c96404d30e)

<br>

In the server config, add the data connection string and database name

![image](https://github.com/Artyom-kurguzkin/CC-ASRS/assets/10873919/7f3f06e2-3767-4d57-ab9e-5aa32d5ce81c)


<br>

### test

Note, we previously configured the load balancer to let HTTP(s) traffic to Nodered. You can find more info about that in the configure_mqtt_node and steps_to_configure_gke documents. 

Look at the previous pictures for the node topology. The inject node was not changed at all. Here is the code from the function node:

```js
msg.find = {};
msg.projection = { "_id": 0, "_location": 1 };
return msg;
```

<br>

Here is what you should see at the end:

![image](https://github.com/Artyom-kurguzkin/CC-ASRS/assets/10873919/7a46774f-fc36-44e8-a0a7-204a03fc3037)






