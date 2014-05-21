// run `nc -ulp 1337` on 192.168.1.102 and you'll receive 'hi', then it'll close

UDP udp;
USBSerial serial;
byte ip[] = {192,168,1,255};
int i = 0;

void setup() {
    serial.begin(9600);
    pinMode(D7, OUTPUT);
}

void loop() {
    
    if (!udp.begin(1337)) {
        serial.write("begin() failed\r\n");
    } else {
        serial.write("begin() succeeded\r\n");
        if (!udp.beginPacket(ip, 50011)) {
            serial.write("beginPacket() failed\r\n");
        } else {
            serial.write("beginPacket() succeeded\r\n");
            udp.write("hi\n");
            serial.write("wrote hi\r\n");
            if (!udp.endPacket()) {
                serial.write("endPacket() failed\r\n");
            } else {
                serial.write("endPacket() succeeded\r\n");
            }
        }
    }
    digitalWrite(D7,HIGH);
    delay(500);
    digitalWrite(D7,LOW);
    delay(1000);
    udp.stop();

}
