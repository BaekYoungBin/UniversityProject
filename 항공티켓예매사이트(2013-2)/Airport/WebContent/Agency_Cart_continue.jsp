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
	String Select = request.getParameter("select");
	
	%>
	<form action="Agency_Reservation.jsp" method="POST" >
	<input type="hidden" name="ID" value="<%=ID%>">
	<input type="hidden" name="select" value="<%=Select%>">	
	<input type="submit" value="����">
	</form>	
	<form action="Agency_Cart_Delete.jsp" method="POST" >
	<input type="hidden" name="ID" value="<%=ID%>">
	<input type="hidden" name="select" value="<%=Select%>">	
	<input type="submit" value="īƮ���� ����">	
	</form>	
	<input type = "button" value = "�ڷ�"	onclick = "history.go(-1)">
</body>
</html>