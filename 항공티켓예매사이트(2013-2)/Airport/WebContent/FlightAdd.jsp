<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>�װ��� ���</title>
</head>
<body>

<%@ page import="java.io.*"%>

	<%@ page import="java.sql.*"%>
	<%String ID = request.getParameter("ID");%>
	<form action="FlightAdd_continue.jsp" method="POST">
	<table border='1'  bordercolor = '#AE52IC'>
	<tr> 
	<td> ������� </td> 
	<td> <input type="text" name="Plane_type"></td>
	</tr>
	<tr> 	
	<td> ����� </td>
	<td> <input type="text" name="Origin"> </td> 
	</tr>
	<tr> 
	<td> ������ </td>
	<td> <input type="text" name="Destination"> </td>
	</tr>
	<tr>
	<td> ��� �ð� </td> 
	<td><input type="text" name="F_time"> </td>
    </tr>		
	<tr> 
	<td> �ҿ� �ð� </td>
	<td> <input type="text" name="Lead_time"> </td>
	</tr>
	<tr> 
	<td> ����  </td>
	 <td>
	    <input type="text" name="Cost"> </td>
	</tr> 
	<tr> 
	<td> ����  </td>
	 <td>
	    <input type="text" name="Sale"> </td>
	</tr>
	<tr> 
	<td> �¼���  </td>
	 <td>
	    <input type="text" name="leftseat"> </td>
	</tr> 
	
	</table>
	<input type="hidden" name="ID" value="<%=ID%>">
	<input type="submit" value="���"> <input type="button" value="���" onclick="history.go(-1)"><input type="reset">
	</form>
</body>
</html>