const API_ROOT = "http://jarvis.local"

let currentConfig = {}

function noOp() {}

// Script to open and close sidebar
function w3_open() {
    document.getElementById("mySidebar").style.display = "block";
    document.getElementById("myOverlay").style.display = "block";
}

function w3_close() {
    document.getElementById("mySidebar").style.display = "none";
    document.getElementById("myOverlay").style.display = "none";
}

// validate and submit configuration
function submitConfiguration(f) {
    currentConfig.hydrometerName = f.hydrometerName.value;
    currentConfig.wifiNetwork = f.wifiNetwork.value;
    currentConfig.wifiPassword = f.wifiPassword.value;
    currentConfig.apiRoot = f.apiRoot.value;
    currentConfig.apiPort = f.apiPort.value;
    currentConfig.apiPath = f.apiPath.value;
    currentConfig.apiKey = f.apiKey.value;
    currentConfig.delaySeconds = f.delaySeconds.value;
    currentConfig.tempCompensationBase = f.tempCompensationBase.value;
    currentConfig.tempCompensationFactor = f.tempCompensationFactor.value;
    currentConfig.bootToHotspot = f.bootToHotspot.checked;
    currentConfig.outputMode = f.outputMode.value;

    sendPOST("/config", currentConfig, updateConfigMain);    
}

function submitTempSensors(f) {
    if(!currentConfig.hasOwnProperty("hydrometerName")) {
        return;
    }

    currentConfig.wortTempAddr = f.wortSensor.value;
    currentConfig.boardTempAddr = f.boardSensor.value;

    sendPOST("/config", currentConfig, updateConfigTemps);    

}

function submitTare(f) {
    const tareRequest = {
        time: f.tareTime.value,
    }
    sendPOST("/tare", tareRequest, noOp);

    window.setTimeout(updateConfigScale, f.tareTime.value * 1000 + 5000);
}

// validate and submit calibration
function submitCalibration(f) {     
    const calibrateRequest = {
        weight: f.calibrationWeight.value,
        time: f.calibrationTime.value,
    }
    sendPOST("/calibrate", calibrateRequest, noOp);

    window.setTimeout(updateConfigScale, f.calibrationTime.value * 1000 + 5000);
}

function submitEquipmentWeight(f) {
    const equipTareRequest = {
        weight: f.equipmentWeight.value,
    }
    sendPOST("/equipmentweight", equipTareRequest, updateConfigScale);
}

function sendPOST(path, object, onFinishedFunction) {
    console.log(object);

    let xmlhttp = new XMLHttpRequest();
    let url = API_ROOT + path;
    
    xmlhttp.onreadystatechange = function() {
        if (this.readyState == 4) {
            if(this.status < 400 && this.status >= 200) {
                onFinishedFunction();
            }
            else {
                console.log("error: " + this.status + " " + this.statusText);
            }
        }
    };
    xmlhttp.open("POST", url, true);
    xmlhttp.send(JSON.stringify(object));
}

function sendCalibrationRequest(calibrationObject) {
    let xmlhttp = new XMLHttpRequest();
    let url = API_ROOT + "/calibrate";
    
    xmlhttp.onreadystatechange = function() {
        if (this.readyState == 4) {
            if(this.status < 400 && this.status >= 200) {
                updateConfig();
            }
            else {
                console.log("error: " + this.status + " " + this.statusText);
            }
        }
    };
    xmlhttp.open("POST", url, true);
    xmlhttp.send(JSON.stringify(calibrationObject));
}

function getConfigRequest(callback) {
    let xmlhttp = new XMLHttpRequest();
    let url = API_ROOT + "/config";
    xmlhttp.onreadystatechange = function() {
        if(this.readyState == 4) {
            if(this.status == 200) {
                currentConfig = this.response;
            }
            callback(this);
        }
    }
    xmlhttp.overrideMimeType("application/json");
    xmlhttp.responseType = "json";
    xmlhttp.open("GET", url, true);
    xmlhttp.send();
}

function updateConfigLive() {
    getConfigRequest(function(xmlhttp) {
        if(xmlhttp.status == 200) {
            document.getElementById("hydrometerNameHeading").innerText = currentConfig.hydrometerName;
        }
        else {
            console.log("error: " + this.status + " " + this.statusText);
        }
    
    });
}

function updateConfigMain() {
    getConfigRequest(function(xmlhttp) {
        if(xmlhttp.status < 400 && xmlhttp.status >= 200) {                
            document.getElementById("hydrometerNameHeading").innerText = currentConfig.hydrometerName;
            document.getElementById("hydrometerName").value = currentConfig.hydrometerName;
            document.getElementById("wifiNetwork").value = currentConfig.wifiNetwork;
            document.getElementById("wifiPassword").value = currentConfig.wifiPassword;
            document.getElementById("apiRoot").value = currentConfig.apiRoot;
            document.getElementById("apiPath").value = currentConfig.apiPath;
            document.getElementById("apiPort").value = currentConfig.apiPort;
            document.getElementById("apiKey").value = currentConfig.apiKey;
            document.getElementById("delaySeconds").value = currentConfig.delaySeconds;
            document.getElementById("tempCompensationBase").value = currentConfig.tempCompensationBase;
            document.getElementById("tempCompensationFactor").value = currentConfig.tempCompensationFactor;
            document.getElementById("bootToHotspot").checked = currentConfig.bootToHotspot;
            document.getElementById("outputMode").value = currentConfig.outputMode;
        }
        else {
            console.log("error: " + this.status + " " + this.statusText);
        }
    });
}

function updateConfigScale() {
    getConfigRequest(function(xmlhttp) {
        if(xmlhttp.status < 400 && xmlhttp.status >= 200) {
            document.getElementById("hydrometerNameHeading").innerText = currentConfig.hydrometerName;
            document.getElementById("tareOffset").value = currentConfig.tareOffset;
            document.getElementById("scaleFactor").value = currentConfig.scaleFactor;
            document.getElementById("equipmentWeight").value = currentConfig.equipmentWeight + "g";
        }
        else {
            console.log("error: " + this.status + " " + this.statusText);
        }
    });
}

function updateConfigTemps() {
    getConfigRequest(function(xmlhttp) {
        if(xmlhttp.status < 400 && xmlhttp.status >= 200) {
            document.getElementById("hydrometerNameHeading").innerText = currentConfig.hydrometerName;
        }
        else {
            console.log("error: " + this.status + " " + this.statusText);
        }
    });
}

function updateLive() {
    let xmlhttp = new XMLHttpRequest();
    let url = API_ROOT + "/live";
    
    xmlhttp.onreadystatechange = function() {
        if (this.readyState == 4) {
            if(this.status < 400 && this.status >= 200) {
                let update = this.response;
                
                document.getElementById("measuredWeight").value = update.calibratedWeight + "g";
                document.getElementById("measuredGravity").value = update.gravity;
                document.getElementById("measuredTemperature").value = update.wortTemperature;
            }
            else {
                console.log("error: " + this.status + " " + this.statusText);
            }
        }
    };
    xmlhttp.overrideMimeType("application/json");
    xmlhttp.responseType = "json";
    xmlhttp.open("GET", url, true);
    xmlhttp.send();
}

function liveRepeat() {
    updateLive();
    setTimeout(liveRepeat, 10000);
}

function updateScale() {
    let xmlhttp = new XMLHttpRequest();
    let url = API_ROOT + "/live";
    
    xmlhttp.onreadystatechange = function() {
        if (this.readyState == 4) {
            if(this.status < 400 && this.status >= 200) {
                let update = this.response;
                
                document.getElementById("rawWeight").value = update.rawWeight;
                document.getElementById("calibratedWeight").value = update.calibratedWeight + "g";
            }
            else {
                console.log("error: " + this.status + " " + this.statusText);
            }
        }
    };
    xmlhttp.overrideMimeType("application/json");
    xmlhttp.responseType = "json";
    xmlhttp.open("GET", url, true);
    xmlhttp.send();
}

function scaleRepeat() {
    updateScale();
    setTimeout(scaleRepeat, 10000);
}

function updateTemps() {
    let xmlhttp = new XMLHttpRequest();
    let url = API_ROOT + "/tempsensors";
    
    xmlhttp.onreadystatechange = function() {
        if (this.readyState == 4) {
            if(this.status < 400 && this.status >= 200) {
                let update = this.response;

                trySetupTempSelects(update.sensors);
                update.sensors.forEach(function(sensor, index){
                    document.getElementById("tempID" + index).value = sensor.id;
                    document.getElementById("tempOutput" + index).value = sensor.temp;
                });
            }
            else {
                console.log("error: " + this.status + " " + this.statusText);
            }
        }
    };
    xmlhttp.overrideMimeType("application/json");
    xmlhttp.responseType = "json";
    xmlhttp.open("GET", url, true);
    xmlhttp.send();
}

function trySetupTempSelects(sensors) {
    const wortSelect = document.getElementById("wortSensor");
    const boardSelect = document.getElementById("boardSensor");

    if(wortSelect.length == 1 && sensors.length > 0) {
        for(let i = 0; i < sensors.length; i++) {
            let option = document.createElement("option");
            option.text = sensors[i].id;
            option.value = option.text;
            wortSelect.add(option);
        }

        if(currentConfig.wortTempAddr > 0) {
            wortSelect.value = currentConfig.wortTempAddr;
        }
    }

    if(boardSelect.length == 1 && sensors.length > 0) {
        for(let i = 0; i < sensors.length; i++) {
            let option = document.createElement("option");
            option.text = sensors[i].id;
            option.value = option.text;
            boardSelect.add(option);
        }

        if(currentConfig.boardTempAddr > 0) {
            boardSelect.value = currentConfig.boardTempAddr;
        }
    }
}

function tempRepeat() {
    updateTemps();
    setTimeout(tempRepeat, 10000);
}