-- MariaDB dump 10.17  Distrib 10.5.5-MariaDB, for Win64 (AMD64)
--
-- Host: localhost    Database: diary
-- ------------------------------------------------------
-- Server version	10.5.5-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `diaryinfo`
--

DROP TABLE IF EXISTS `diaryinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `diaryinfo` (
  `id` varchar(30) DEFAULT NULL,
  `date` date DEFAULT NULL,
  `title` varchar(100) DEFAULT NULL,
  `contents` longtext DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `diaryinfo`
--

LOCK TABLES `diaryinfo` WRITE;
/*!40000 ALTER TABLE `diaryinfo` DISABLE KEYS */;
INSERT INTO `diaryinfo` VALUES ('test','2021-01-18','눈이 내린다','코로나가 얼른 끝났으면 좋겠다.'),('test','2021-01-05','계절학기 강의 시작!','얼른 강의 듣고 싶다'),('test','2020-12-25','메리 솔로 크리스마스','ㅠㅠㅠ'),('test','2020-01-15','군대 전역하고 한달','아직도 아침 6시반에만 되면 눈이 떠진다.'),('test','2021-01-12','조별과제 파이팅 ㅠㅠ','우리조 파이팅!'),('test','2021-01-01','신년','공부 좀 열심히 해보자'),('test','2021-01-17','최종보고서 제출날','잊지 말고 제출하자'),('test','2021-01-16','친구들이랑 약속 있는날','5명까지 못모이는게 아쉽다 ㅠㅠ 얼굴만 보고 돌아와야지.'),('test2','2021-01-01','신년','올해는 코딩공부 열심히 해보자');
/*!40000 ALTER TABLE `diaryinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `idinfo`
--

DROP TABLE IF EXISTS `idinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `idinfo` (
  `id` varchar(30) DEFAULT NULL,
  `pwd` varchar(30) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `idinfo`
--

LOCK TABLES `idinfo` WRITE;
/*!40000 ALTER TABLE `idinfo` DISABLE KEYS */;
INSERT INTO `idinfo` VALUES ('test','1234'),('test2','1234');
/*!40000 ALTER TABLE `idinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `svrinfo`
--

DROP TABLE IF EXISTS `svrinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `svrinfo` (
  `id` varchar(30) DEFAULT NULL,
  `date` date DEFAULT NULL,
  `title` varchar(100) DEFAULT NULL,
  `contents` longtext DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `svrinfo`
--

LOCK TABLES `svrinfo` WRITE;
/*!40000 ALTER TABLE `svrinfo` DISABLE KEYS */;
INSERT INTO `svrinfo` VALUES ('test','2021-01-18','눈이 내린다','코로나가 얼른 끝났으면 좋겠다.'),('test','2021-01-05','계절학기 강의 시작!','얼른 강의 듣고 싶다'),('test','2021-01-12','조별과제 파이팅 ㅠㅠ','우리조 파이팅!'),('test','2020-01-15','군대 전역하고 한달','아직도 아침 6시반에만 되면 눈이 떠진다.'),('test','2021-01-01','신년','공부 좀 열심히 해보자'),('test','2021-01-17','최종보고서 제출날','잊지 말고 제출하자'),('test','2021-01-16','친구들이랑 약속 있는날','5명까지 못모이는게 아쉽다 ㅠㅠ 얼굴만 보고 돌아와야지.'),('test2','2021-01-01','신년','올해는 코딩공부 열심히 해보자');
/*!40000 ALTER TABLE `svrinfo` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-01-15 17:57:49
