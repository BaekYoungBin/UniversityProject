<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>회원가입</title>
</head>
<body>

	<%@ page import="java.io.*"%>
	<%@ page import="java.sql.*"%>
	<form action="Customer_Enrollment_continue.jsp" method="POST">
	<table border='1'  bordercolor = '#AE52IC'>
	<tr> 
		<td> ID </td> 
		<td> <input type="text" name="ID"></td>
	</tr>
	<tr> 
	<td> Password <BR>
		 Password confirm </td>
	<td> <input type="password" name="pwd"><BR>
	     <input type="password" name="pwd_conf"></td>
	</tr> 
	<tr> 
	<td> Name </td>
	<td> <input type="text" name="name"> </td>
	</tr>
	<tr> 
	<td> Age </td>
	<td> <input type="text" name="age"> </td>
	</tr>
	<tr>
	<td> Gender </td> 
	<td>
	   <input type="radio" name="gender" value="Male"> Male
       <input type="radio" name="gender" value="Female"> Female
    </td>
    </tr>
		
	<tr> 
	<td> Address </td>
	<td> <input type="text" name="address"> </td>
	</tr>
	<tr> 
	<td> Phone_number </td>
	 <td>
	    <input type="text" name="phone"> </td>
	</tr> 
	</table>
	
	<input type="submit" value="등록"> <input type="button" value="취소" onclick="history.go(-1)"><input type="reset">
	</form>
	
</body>
</html>