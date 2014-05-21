// run `nc -ulp 1337` on 192.168.1.101 and you'll receive 'hi', then it'll close

const int UDP_MSG_LEN = 1024;
UDP udp;
USBSerial serial;
byte ip[] = {192, 168, 1, 101};
int i = 0;
int start;
int end;
double rate;
char ser_message[32] = "";
char udp_message[512];

void setup() {
    serial.begin(9600);
    pinMode(D7, OUTPUT);
    for(i=0;i<512;i++) {udp_message[i] = '1';}

}

void loop() {
    if (!udp.begin(1337)) {
        serial.write("begin() failed\r\n");
        return;
    }

    
    start = millis();
    for(i = 0; i < 500; i++) {
        udp.beginPacket(ip, 1337);
        udp.write('0');
        udp.endPacket();
    }
    end = millis();
    rate = 0.001*500*(end - start);
    sprintf(ser_message, "%4.2f per sec\r\n", rate);
    serial.write(ser_message);


    delay(1000);
    udp.stop();

}
