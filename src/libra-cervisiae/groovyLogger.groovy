println "sequence#,date,boardTemp,rawWeight,calibratedWeight"

int seq = 0;

while(true) {
    def connection = new URL("http://jarvis.local/live").openConnection() as HttpURLConnection

    def text = connection.inputStream.text;
    def json = new groovy.json.JsonSlurper().parseText(text);

    println "${seq++},${new Date().format("MM/dd/yyyy HH:mm:ss")},$json.boardTemperature,$json.rawWeight,$json.calibratedWeight"

    sleep(1000 * 60 * 10);
}


