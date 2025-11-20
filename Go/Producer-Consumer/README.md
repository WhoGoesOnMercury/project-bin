# Producer-Consumer




## Requirements

- **Docker**: Install [Docker Desktop](https://www.docker.com/get-started) (Windows/macOS) or Docker Engine (Linux).  
- **Docker Compose**: Usually included with Docker Desktop. Verify with:

```bash
docker-compose --version
```

Once you have the entire project folder, download this [UNZIP.zip](https://drive.google.com/file/d/177cySeirtpgpn8XOWCO2gr5voR2Z-b5r/view?usp=sharing)
file. Unzip and place the extracted files into a folder named videos (if there is no videos folder, create one first). Alternatively, you can place
your own videos into the folder. Afterwards, you can run these commands sequentially:

```bash
docker-compose build   // For building the container images
docker-compose up      // For starting the application
```

You can then access the local application through localhost:8080. When you are down, close the application using:

```bash
docker-compose down    // For tearing down the containers, essentially turning the application off
```
