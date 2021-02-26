db 세팅은 https://blog.naver.com/tipsware/221304492974
https://blog.naver.com/tipsware/221304774640
이 블로그를 많이 참조 하였습니다.

db세팅부분은 혹시 사용하시는 방법이 저희와 조금 다를까 싶어
서 저희가 했던 mysql odbc 세팅 순서를 적어 봤습니다.
1. mysql-connector-odbc-8.0.22-winx64 설치(동봉되어 있습니다)
2. 제어판 -> 시스템 및 보안 -> 관리도구 
->ODBC 데이터 원본(64비트) 실행
3. 사용자 DSN->추가->MySQL ODBC 8.0 Unicode Driver 실행
4. Data Source Name, User, Password 입력하시고 ok -> 확인
(저희는 로컬호스트를 사용 했습니다.

코드에서 수정하셔야되는 부분
project 파일 projectDlg.cpp 126, 127, 128번째 줄.
SocketServer 파일 SocketServerDlg 133, 134, 135번째 줄.
datasource name과 user, id를 교수님 db 기준으로 수정해주세요

sqldump 파일인 installme 파일과 connector 프로그램을 같이
제출하겠습니다. sql 파일 쓰시면 테스트값이 조금 넣어져 있는
버젼으로 diary 란 이름의 db가 생성될 겁니다.
혹시몰라서 테이블 생성부분 코드 같이 넣어봅니다.
create table svrinfo
(
id varchar(30),
date date,
title varchar(100),
contents longtext
);
create table Diaryinfo
(
id varchar(30),
date date,
title varchar(100),
contents longtext
);
create table idinfo
(
    id varchar(30),
    pwd varchar(30)
);
