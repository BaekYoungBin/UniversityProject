<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>YB항공</title>
</head>
<body>
<%@ page import = "java.io.*" %>

	<form  action = "LoginCheck.jsp" method = "POST">
	<h2> 항공 예약 시스템입니다. </h2>
	<input type = "radio" name = "LoginType" value = "Customer" checked>일반회원
	<input type = "radio" name = "LoginType" value = "Manager">관리자
	<input type = "radio" name = "LoginType" value = "Employee">항공사 직원
	<input type = "radio" name = "LoginType" value = "Agency"> 여행사
	<table border='1'  bordercolor = '#AE52IC'>
	<tr>
		<td> ID </td>
		<td> <input type = "text" name = "ID"> </td>
	</tr>
	<tr>
	<td> Password  </td>
	<td> <input type = "password" name = "pwd"> <BR>
	</td>
		</tr>
		</table>	
		<input type = "submit" value = "로그인">	
			</form>
<form  action = "Customer_Enrollment.jsp" method = "POST">
<input type = "submit" value = "회원가입">	
</form>

</body>
</html>
