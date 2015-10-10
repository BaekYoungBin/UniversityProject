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
	String Plane_Type = request.getParameter("Plane_Type");
	String Origin = "null";
	String Destination = "null";
	String F_time = "null";
	String Lead_time = "null";
	String Cost = "null";
	String Sale = "null";

		%>
		<form  action = "FlightInsert_continue_2.jsp" method = "POST">
		<table border='1'  bordercolor = '#AE52IC'>
				<tr>
				<td> Plane_type </td>
				<td> Origin</td>
				<td> Destination </td>
				<td> F_Time </td>
				<td> Lead_Time </td>
				<td> Cost</td>
				<td> Sale </td>
				<td> Left_seat </td>
				
				</tr>
				<tr>		
				<td> <%=Plane_Type %></td>
				<td> <input type = "text" name = "Origin" style ="width:50px; height = 20px;"/></td>
				<td> <input type = "text" name = "Destination" style ="width:50px; height = 20px;"/></td>			
				<td> <input type = "text" name = "F_Time" style ="width:80px; height = 20px;"/></td>
				<td> <input type = "text" name = "Lead_Time" style ="width:50px; height = 20px;"/></td>
				<td> <input type = "text" name = "Cost" style ="width:50px; height = 20px;"/></td>
				<td> <input type = "text" name = "Sale" style ="width:30px; height = 20px;"/></td>
				<td> <input type = "text" name = "leftseat" style ="width:30px; height = 20px;"/></td>					
				</tr>
				</table>
			<input type="hidden" name="Plane_Type" value="<%=Plane_Type%>">
			<input type="hidden" name="ID" value="<%=ID%>">
			<input type = "submit" value = "저장"><input type="reset">
			<input type="button" value="뒤로" onclick="history.go(-1)">				
			</form>
				
		<%
		
	
		
		
		
		%>
</body>
</html>