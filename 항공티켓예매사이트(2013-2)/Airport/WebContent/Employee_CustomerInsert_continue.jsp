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
	<%

	String ID = request.getParameter("ID");
	String C_ID = request.getParameter("C_ID");
	String Origin = "null";
	String Destination = "null";
	String F_time = "null";
	String Lead_time = "null";
	String Cost = "null";
	String Sale = "null";
	
		%>
		<form  action = "Employee_CustomerInsert_continue2.jsp" method = "POST">
		<table border='1'  bordercolor = '#AE52IC'>
				<tr>
				<td> ID </td>
				<td> Password</td>
				<td> 이름 </td>
				<td> 나이</td>
				<td> 성별</td>
				<td> 주소</td>
				<td> 전화번호 </td>
				<td> 랭크 </td>
				<td> 마일리지</td>
				</tr>
				<tr>
				
				<td> <%=C_ID %></td>			
				<td> <input type = "password" name = "PS" style ="width:80px; height = 20px;"/></td>
				<td> <input type = "text" name = "Name" style ="width:50px; height = 20px;"/></td>
				<td> <input type = "text" name = "Age" style ="width:30px; height = 20px;"/></td>
				<td> <input type = "text" name = "Gender" style ="width:30px; height = 20px;"/></td>
				<td> <input type = "text" name = "Address" style ="width:100px; height = 20px;"/></td>
				<td> <input type = "text" name = "Phone" style ="width:100px; height = 20px;"/></td>
				<td> <input type = "text" name = "Rank" style ="width:100px; height = 20px;"/></td>
				<td> <input type = "text" name = "Mileage" style ="width:100px; height = 20px;"/></td>
				</tr>
				</table>
				<input type="hidden" name="ID" value="<%=ID%>">
			<input type="hidden" name="C_ID" value="<%=C_ID%>">
			<input type="submit" value = "저장"><input type="reset">
			<input type="button" value="취소" onclick="history.go(-1)">				
			</form>
				
		<%
		
	
		
		
		
		%>
</body>
</html>