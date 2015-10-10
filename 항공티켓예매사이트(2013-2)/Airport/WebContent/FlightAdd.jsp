<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>항공편 등록</title>
</head>
<body>

<%@ page import="java.io.*"%>

	<%@ page import="java.sql.*"%>
	<%String ID = request.getParameter("ID");%>
	<form action="FlightAdd_continue.jsp" method="POST">
	<table border='1'  bordercolor = '#AE52IC'>
	<tr> 
	<td> 비행기종 </td> 
	<td> <input type="text" name="Plane_type"></td>
	</tr>
	<tr> 	
	<td> 출발지 </td>
	<td> <input type="text" name="Origin"> </td> 
	</tr>
	<tr> 
	<td> 목적지 </td>
	<td> <input type="text" name="Destination"> </td>
	</tr>
	<tr>
	<td> 출발 시간 </td> 
	<td><input type="text" name="F_time"> </td>
    </tr>		
	<tr> 
	<td> 소요 시간 </td>
	<td> <input type="text" name="Lead_time"> </td>
	</tr>
	<tr> 
	<td> 가격  </td>
	 <td>
	    <input type="text" name="Cost"> </td>
	</tr> 
	<tr> 
	<td> 세일  </td>
	 <td>
	    <input type="text" name="Sale"> </td>
	</tr>
	<tr> 
	<td> 좌석수  </td>
	 <td>
	    <input type="text" name="leftseat"> </td>
	</tr> 
	
	</table>
	<input type="hidden" name="ID" value="<%=ID%>">
	<input type="submit" value="등록"> <input type="button" value="취소" onclick="history.go(-1)"><input type="reset">
	</form>
</body>
</html>