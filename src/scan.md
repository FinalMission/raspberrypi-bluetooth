## rssi.c 분석
- **hci** : host controller interface
- `int hci_open_dev(int dev_id);`
  - hci 장치를 open 하는 루틴.
  - 리턴값은 **device descriptor(dd)** 이다.
  - 이 함수의 흐름은
    - 디바이스 id의 유효성을 검증한 후,
    - 소켓을 생성한 후,
    - 소켓에 주소를 binding한 후,
    - 성공 시, 파일 디스크립터 번호를
    - 실패 시, -1 리턴한다.

- `htobs(int hex)`
  - hex to byte short의 약자.

- `ble_hci_request(uint16_t ocf, int clen, void * status, void * cparam)`
  - hci_request 타입을 리턴하는 함수.

- `struct hci_request`
```
    struct hci_request {
    	uint16_t ogf;
    	uint16_t ocf;
    	int      event;
    	void     *cparam;
    	int      clen;
    	void     *rparam;
    	int      rlen;
    };
```
  - ogf : opcode group field
  - ocf : opcode command field
  - event : ?
