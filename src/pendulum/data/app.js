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
    const configObject = {
        "hydrometerName": f.hydrometerName.value,
        "wifiNetwork": f.wifiNetwork.value,
        "wifiPassword": f.wifiPassword.value,
        "apiRoot": f.apiRoot.value,
        "apiPath": f.apiPath.value,
        "apiPort": f.apiPort.value,
        "apiKey": f.apiKey.value,
        "delaySeconds": f.delaySeconds.value,
        "fullVoltage": f.fullVoltage.value,
        "tempCompensationBase": f.tempCompensationBase.value,
        "tempCompensationFactor": f.tempCompensationFactor.value,
        "scaleFactor": f.scaleFactor.value,
        "bootToHotspot": f.bootToHotspot.checked,
        "outputMode": f.outputMode.value
    }
    sendConfigRequest(configObject);
    
}

// validate and submit calibration
function submitCalibration(f) {     
    // assemble arrays
    let weights = [];
    let gravities = [];
    
    for(let i = 0; i < 8; i++) {
        let weight = parseFloat(f["weight" + i].value);
        let gravity = parseFloat(f["gravity" + i].value);
        
        if(typeof(weight) === 'number' && typeof(gravity) === 'number' && weight > 0 && gravity > 0) {
            weights.push(weight);
            gravities.push(gravity);
        }
    }
    
    const calibrationObject = {
        "weights": weights,
        "gravities": gravities
    }
    
    if(calibrationObject.gravities.length < 4 || calibrationObject.weights.length < 4) {
        alert("Too few datapoints!");
        return;
    } else if(calibrationObject.gravities.length != calibrationObject.weights.length) {
        alert("Mismatched data lengths!");
        return;
    }
    
    sendCalibrationRequest(calibrationObject);
    
}

function sendConfigRequest(configObject) {
    console.log(configObject);

    let xmlhttp = new XMLHttpRequest();
    let url = "/config";
    
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
    xmlhttp.send(JSON.stringify(configObject));
}

function sendCalibrationRequest(calibrationObject) {
    let xmlhttp = new XMLHttpRequest();
    let url = "/calibration";
    
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

function updateConfig() {
    let xmlhttp = new XMLHttpRequest();
    let url = "/config";
    
    xmlhttp.onreadystatechange = function() {
        if (this.readyState == 4) {
            if(this.status < 400 && this.status >= 200) {
                let config = this.response;
                
                document.getElementById("hydrometerNameHeading").innerText = config.hydrometerName;
                document.getElementById("hydrometerName").value = config.hydrometerName;
                document.getElementById("wifiNetwork").value = config.wifiNetwork;
                document.getElementById("wifiPassword").value = config.wifiPassword;
                document.getElementById("apiRoot").value = config.apiRoot;
                document.getElementById("apiPath").value = config.apiPath;
                document.getElementById("apiPort").value = config.apiPort;
                document.getElementById("apiKey").value = config.apiKey;
                document.getElementById("delaySeconds").value = config.delaySeconds;
                document.getElementById("fullVoltage").value = config.fullVoltage;
                document.getElementById("tempCompensationBase").value = config.tempCompensationBase;
                document.getElementById("tempCompensationFactor").value = config.tempCompensationFactor;
                document.getElementById("scaleFactor").value = config.scaleFactor;
                document.getElementById("bootToHotspot").checked = config.bootToHotspot;
                document.getElementById("outputMode").value = config.outputMode;

                
                document.getElementById("gravityA").value = config.gravityCoefficients[0];
                document.getElementById("gravityB").value = config.gravityCoefficients[1];
                document.getElementById("gravityC").value = config.gravityCoefficients[2];
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

function updateLive() {
    let xmlhttp = new XMLHttpRequest();
    let url = "/live";
    
    xmlhttp.onreadystatechange = function() {
        if (this.readyState == 4) {
            if(this.status < 400 && this.status >= 200) {
                let update = this.response;
                
                document.getElementById("measuredWeight").value = update.weight;
                document.getElementById("measuredGravity").value = update.gravity;
                document.getElementById("measuredTemperature").value = update.temperature;
                document.getElementById("measuredBattery").value = update.battery;
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