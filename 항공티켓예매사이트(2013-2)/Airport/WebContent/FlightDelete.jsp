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
		String DelPlaneType = request.getParameter("Plane_Type");
		String ID = request.getParameter("ID");
		String DB_URL = "jdbc:oracle:thin:@165.132.221.101:1521:XE";
	try{
		DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
		Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@165.132.221.101:1521:XE","db09253072","ghk2xld");
		Statement stmt = conn.createStatement();
		ResultSet rs = stmt.executeQuery("delete from flight where PLANE_TYPE = '"+DelPlaneType+"'");
		out.println("���� �Ϸ�");
		rs.close();
		stmt.close();
		conn.close();
	}
	catch (Exception e){
		out.println("Error");
		e.printStackTrace();
	}
		
	
	%>
	<br> <br> 
	<form action="ManagerMain.jsp" method="POST">
	<input type="hidden" name="ID" value="<%=ID%>">
	<input type="submit" value="HOME">
	</form>
	<input type = "button" value = "�ڷ�"  onclick = "history.go(-1)">
</body>
</html>