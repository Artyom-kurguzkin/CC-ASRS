1. create default gke cluster

<br>

2. create config files in your current directory. Files are in this folder. 

```bash
$ touch ./manifest.yaml
$ touch .nodered-service.yaml
```

<br>

3. Apply configs

```bash
kubectl apply -f manifest.yaml
kubectl apply -f nodered-service.yaml

kubectl describe deployment | grep Ports
kubectl get services
```

- external ip for nodered-service is now accessible from your broweser

<br>

---

<br>

4. put password on nodered. this one has issues. Settings are not presistent with deployment, so they are wiped out whenever the container is redepoloyed. 

First, access the kubernetes pod we have set up.

```bash
$ kubectl get pods
$ kubectl exec -it <pod-name> -- /bin/bash
```

```bash
$ cd .node-red/
$ nano settings.js
```
* note, if you can't find the file, use `find / -name settings.json` command.



uncomment the whole `adminAuth:{},` section. We will come back here.

* to locate the string, use `ctrl + w` - activates search in nano



We need to change password hash in that section. Exit or open a new terminal session.

```bash
$ node-red admin hash-pw
$ <- Password of your choosing
$ -> hash
```

go back to the config file and insert the new hash in place of the old one. Restart nodered

```bash
$ node-red -restart
```

