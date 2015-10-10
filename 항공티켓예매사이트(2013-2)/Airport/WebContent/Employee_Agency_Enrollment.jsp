<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>Insert title here</title>
</head>
<body>
<%@ page import="java.io.*"%>
	<%@ page import="java.sql.*"%>
	<%String ID = request.getParameter("ID");
 %>
	<form action="Employee_Agency_Enrollment_continue.jsp" method="POST">
	<table border='1'  bordercolor = '#AE52IC'>
	<tr> 
		<td> AgencyID </td> 
		<td> <input type="text" name="A_ID"></td>
	</tr>
	<tr> 
	<td> Password <BR>
		 Password confirm </td>
	<td> <input type="password" name="pwd"><BR>
	     <input type="password" name="pwd_conf"></td>
	</tr> 
	<tr> 
	<td> Agency_Name </td>
	<td> <input type="text" name="A_Name"> </td>
	</tr>
	
	<tr> 
	<td> Agency_Address </td>
	<td> <input type="text" name="A_address"> </td>
	</tr>
	<tr> 
	<td> Agency_Phone_number </td>
	 <td>
	    <input type="text" name="A_phone"> </td>
	</tr> 
	</table>
	
	<input type="submit" value="등록"> <input type="button" value="취소" onclick="history.go(-1)"><input type="reset">
	<input type="hidden" name="ID" value="<%=ID%>">
	</form>
</body>
</html>