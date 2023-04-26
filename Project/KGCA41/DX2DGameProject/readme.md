# Top Gun
![image](https://user-images.githubusercontent.com/40855235/234495299-890e6b87-bbff-43b4-b2f6-a77ee35f45c5.png)

DirectX를 이용한 2D Project

## 시놉시스
![image](https://user-images.githubusercontent.com/40855235/234496274-058bbf45-3058-468c-9271-ddcf770c8b33.png)


## 구현 기술
![image](https://user-images.githubusercontent.com/40855235/234495390-b12cf1df-5b09-465b-a031-5ec40128ae57.png)
![image](https://user-images.githubusercontent.com/40855235/234495402-f9283dc7-5366-4054-aec7-3ef8e57201e1.png)
![image](https://user-images.githubusercontent.com/40855235/234495418-2d0e07cf-89a1-4db9-b0aa-c30799086bfc.png)

3D라는 비행기의 특성을 2D게임에서 구현할 수 있도록하기 위해 Layer라는 개념을 도입했습니다.

![image](https://user-images.githubusercontent.com/40855235/234495422-40aa293f-23cb-4190-9f8a-524720034fff.png)

Layer를 통한 고도감을 줄 수 있도록 높은 Layer에 위치할 경우 Object의 크기를 더 크게, 낮은 Layer에 위치할 경우 Object의 크기를 더 작게 출력했습니다.

![image](https://user-images.githubusercontent.com/40855235/234495429-ccd5f445-894a-465e-af8b-ae587f093bea.png)

짧고 빠르게 지나가는 바다 Tile의 Memory를 관리하고 새로 생성하는데 필요한 시간을 줄일 수 있도록 하기위해 Memory Pool을 사용했습니다.

![image](https://user-images.githubusercontent.com/40855235/234496037-ce894960-182d-4a72-b34b-a5c0219990c8.png)

제한시간 등 User에게 보여야하는 Text의 Font를 적용하기 위해 DirectWrite가 아닌 Texture를 동적으로 배치할 수 있는 기술을 구현했습니다.

## 조작법
![image](https://user-images.githubusercontent.com/40855235/234496162-132b3115-4e88-41dc-82d7-d137caa003b0.png)
![image](https://user-images.githubusercontent.com/40855235/234496170-532cf16b-0faa-48c4-a995-eac60d541874.png)
![image](https://user-images.githubusercontent.com/40855235/234496177-fe389a92-6231-42e2-a64b-819cf1d36bce.png)
![image](https://user-images.githubusercontent.com/40855235/234496192-1ec6c53e-f777-4eb0-97ef-a02e1268aecb.png)

## 목표
![image](https://user-images.githubusercontent.com/40855235/234496229-e243fc4c-a762-4f20-b11d-69b2b6ffa4be.png)

## 동영상
https://www.youtube.com/watch?v=TbB69kr_9q4

## 다운로드
http://naver.me/G8tx6SwT
