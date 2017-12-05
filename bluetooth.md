- [원본](http://www.hardcopyworld.com/ngine/aduino/index.php/archives/1132)

## GAP
>  GAP는 Generic Access Profile의 약자로 블루투스에서 게시(advertising)와 연결(connection)을 제어한다.
GAP은 장치들이 맡을 수 있는 다양한 역할들에 대해 정의한다. 그 중 가장 핵심이 되는 컨셉은 Central 장치와 Peripheral 장치.

>Peripheral 장치는 주로 작고, 저전력으로 동작한다.제한된 리소스를 가진 장치들로 보다 리소스가 풍부한 Central 장치에 연결되어 동작하도록 설계된 장치

> Central 장치는 태블릿과 같이 충분한 전원과 메모리 등의 리소스를 갖춘 장치.

## Advertising and Scan Response Data
> GAP을 이용해서 게시(Advertising)를 할 때 Advertising Data Payload와 Scan Response Payload 를 포함할 수 있다.

> 두 가지는 서로 구분되며 31바이트까지 데이터를 포함할 수 있다. 하지만 Advertising Data Payload 가 필수인데 반해 Scan Response Payload는 선택적이다.

> Advertising Data Payload 는 Central 장치가 인식할 수 있도록 peripheral 장치(센서장치)에서 계속 송출되는 데이터입니다. Scan Response Payload 는 central 장치(폰)에서 장치 이름과 같이 추가적인 정보를 요구하기 위해 정의된 것으로 선택적으로 구현된다.

- 센서장치가 advertising interval를 가지고 이 주기마다 advertising packet을 날린다.

> Peripheral 장치는 31바이트 정도의 작은 데이터를 실어서 게시(advertising)를 함으로써 낮은 비용으로 주변의 central 장치에 자신의 존재를 알릴 수 있다. BLE에서는 이것을 Broadcasting 이라 한다.

## 용어
- **GATT (Generic Attribute Profile)** : GATT는 두 BLE 장치간에 Service, Characteristic 을 이용해서 데이터를 주고 받는 방법을 정의한 것입니다.

- **Attribute Protocol (ATT)** : GATT는 ATT의 최상위 구현체이며 GATT/ATT로 참조되기도 합니다. 각각의 속성(Attribute)은 UUID를 가지며 128비트로 구성됩니다. ATT에 의해 부여된 속성은 특성(characteristic)과 서비스(Service)를 결정합니다.

- **Characteristic** : 하나의 특성(characteristic)은 하나의 값과 n개의 디스크립터를 포함합니다.

- **Descriptor** : 디스크립터는 특성의 값을 기술합니다.
Service : 하나의 서비스는 특성들의 집합입니다. 예를 들어 “Heart Rate Monitor”라고 불리는 서비스를 가지고 있다면 그 서비스는 “heart rate measurement”같은 특성을 포함합니다.

## 역할에 따른 구분
**Central / Peripheral**
BLE 로 연결되기 위한 서로의 역할을 구분한 것입니다.
central 은 scan, 게시검색(looking for advertisement)을 담당.
peripheral 은 게시(advertisement)를 만든다.
예를들어 폰과 센서장치가 있다면 폰이 주변의 센서장치를 스캔하는 역할을 할 것이므로 central 이 됩니다. 반대로 센서장치가 peripheral 이 됩니다. 중요한 점은 peripheral 은 오로지 하나의 central 장치에만 연결될 수 있습니다. peripheral 이 central 에 연결되면 게시(advertising)를 중단하기 때문입니다. 따라서 다른 central 장치는 peripheral의 연결이 해제될 때 까지 찾을 수 없습니다.

**GATT server(slave) / GATT client(master)**

BLE 장치가 연결된 이후 어떻게 서로 통신하는지에 대해 정의합니다. 일반적으로 peripheral 장치(센서장치)가 GATT server 역할을 하며 ATT lookup data, service, characteristic 에 대한 정의를 가지고 있습니다. GATT client(폰, 태블릿 등)에서는 GATT server 로 데이터 요청을 보냅니다. 모든 동작(transaction)은 GATT client 에서 시작되어 GATT server로 부터 응답을 받게 됩니다.

두 장치가 연결될 때 peripheral(센서장치) 은 연결간격(connection interval)을 전달합니다. Central(폰)은 이 시간만큼 간격을 두고 새로운 데이터가 있는지 재연결을 시도할 수 있습니다. 하지만 이것은 필수 사항은 아닙니다.
