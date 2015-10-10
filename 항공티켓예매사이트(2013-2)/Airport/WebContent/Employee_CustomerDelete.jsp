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
		String Delete_ID = request.getParameter("C_ID");
	
		String DB_URL = "jdbc:oracle:thin:@165.132.221.101:1521:XE";
	try{
		DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
		Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@165.132.221.101:1521:XE","db09253072","ghk2xld");
		Statement stmt = conn.createStatement();
		ResultSet rs = stmt.executeQuery("delete from flight where PLANE_TYPE = '"+Delete_ID+"'");
		out.println("삭제 완료");
		rs.close();
		stmt.close();
		conn.close();
	}
	catch (Exception e){
		out.println("Error");
		e.printStackTrace();
	}
		
	
	%>
	<br> <br> <form action="EmployeeMain.jsp" method="POST">
	<input type="hidden" name="ID" value="<%=ID%>">
	                         <input type="submit" value="HOME">
	                         </form>
</body>
</html>