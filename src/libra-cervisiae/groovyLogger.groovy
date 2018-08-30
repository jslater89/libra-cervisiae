println "sequence#,date,boardTemp,rawWeight,calibratedWeight,wortTemp,abw,abv,gravity"

int seq = 0;

while(true) {
    try {
        def connection = new URL("http://vision.local/live").openConnection() as HttpURLConnection

        def text = connection.inputStream.text;
        def json = new groovy.json.JsonSlurper().parseText(text);

        println "${seq++},${new Date().format("MM/dd/yyyy HH:mm:ss")},$json.boardTemperature,$json.rawWeight,$json.calibratedWeight,$json.wortTemperature,$json.abw,$json.abv,$json.gravity"
    }
    catch(Exception e) {}

    sleep(1000 * 60 * 10);
}


