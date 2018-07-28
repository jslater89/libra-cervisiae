const API_ROOT = "http://jarvis.local"

let currentConfig = {}

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

    sendConfigRequest(currentConfig);    
}

function submitTare(f) {
    // TODO
}

// validate and submit calibration
function submitCalibration(f) {     
    // TODO
}

function submitEquipmentWeight(f) {
    // TODO
}

function sendConfigRequest(configObject) {
    console.log(configObject);

    let xmlhttp = new XMLHttpRequest();
    let url = API_ROOT + "/config";
    
    xmlhttp.onreadystatechange = function() {
        if (this.readyState == 4) {
            if(this.status < 400 && this.status >= 200) {
                updateConfigMain();
            }
            else {
                console.log("error: " + this.status + " " + this.statusText);
            }
        }
    };
    xmlhttp.open("POST", url, true);
    xmlhttp.send(JSON.stringify(configObject));
}

function sendCalibrationRequest(calibrationObject) {
    let xmlhttp = new XMLHttpRequest();
    let url = API_ROOT + "/calibration";
    
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

function getCalibrationRequest(callback) {
    let xmlhttp = new XMLHttpRequest();
    let url = API_ROOT + "/config";
    xmlhttp.onreadystatechange = function() {
        currentConfig = this.response;
        callback(this);
    }
    xmlhttp.overrideMimeType("application/json");
    xmlhttp.responseType = "json";
    xmlhttp.open("GET", url, true);
    xmlhttp.send();
}

function updateConfigLive() {
    getCalibrationRequest(function(xmlhttp) {
        if (xmlhttp.readyState == 4) {
            if(xmlhttp.status < 400 && xmlhttp.status >= 200) {
                let config = xmlhttp.response;
                document.getElementById("hydrometerNameHeading").innerText = config.hydrometerName;
            }
            else {
                console.log("error: " + this.status + " " + this.statusText);
            }
        }
    });
}

function updateConfigMain() {
    getCalibrationRequest(function(xmlhttp) {
        if (xmlhttp.readyState == 4) {
            if(xmlhttp.status < 400 && xmlhttp.status >= 200) {
                let config = xmlhttp.response;
                
                document.getElementById("hydrometerNameHeading").innerText = config.hydrometerName;
                document.getElementById("hydrometerName").value = config.hydrometerName;
                document.getElementById("wifiNetwork").value = config.wifiNetwork;
                document.getElementById("wifiPassword").value = config.wifiPassword;
                document.getElementById("apiRoot").value = config.apiRoot;
                document.getElementById("apiPath").value = config.apiPath;
                document.getElementById("apiPort").value = config.apiPort;
                document.getElementById("apiKey").value = config.apiKey;
                document.getElementById("delaySeconds").value = config.delaySeconds;
                document.getElementById("tempCompensationBase").value = config.tempCompensationBase;
                document.getElementById("tempCompensationFactor").value = config.tempCompensationFactor;
                document.getElementById("bootToHotspot").checked = config.bootToHotspot;
                document.getElementById("outputMode").value = config.outputMode;
            }
            else {
                console.log("error: " + this.status + " " + this.statusText);
            }
        }
    });
}

function updateConfigScale() {
    getCalibrationRequest(function(xmlhttp) {
        if (xmlhttp.readyState == 4) {
            if(xmlhttp.status < 400 && xmlhttp.status >= 200) {
                let config = xmlhttp.response;
                document.getElementById("hydrometerNameHeading").innerText = config.hydrometerName;
            }
            else {
                console.log("error: " + this.status + " " + this.statusText);
            }
        }
    });
}

function updateConfigTemps() {
    getCalibrationRequest(function(xmlhttp) {
        if (xmlhttp.readyState == 4) {
            if(xmlhttp.status < 400 && xmlhttp.status >= 200) {
                let config = xmlhttp.response;
                document.getElementById("hydrometerNameHeading").innerText = config.hydrometerName;
            }
            else {
                console.log("error: " + this.status + " " + this.statusText);
            }
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
                
                document.getElementById("measuredWeight").value = update.weight;
                document.getElementById("measuredGravity").value = update.gravity;
                document.getElementById("measuredTemperature").value = update.temperature;
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