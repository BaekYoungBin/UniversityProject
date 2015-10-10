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
	String I_PS = request.getParameter("PS");
	String I_Name = request.getParameter("Name");
	String I_Age = request.getParameter("Age");
	String I_Gender = request.getParameter("Gender");
	String I_Address = request.getParameter("Address");
	String I_Phone = request.getParameter("Phone");
	String I_Rank = request.getParameter("Rank");
	String I_Mileage = request.getParameter("Mileage");
	out.print("OK");
	
	String DB_URL = "jdbc:oracle:thin:@165.132.221.101:1521:XE";
			
	try{
		out.print("OK");
				
			DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
			Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@165.132.221.101:1521:XE","db09253072","ghk2xld");
			Statement stmt = conn.createStatement();
			ResultSet rs;			
				rs = stmt.executeQuery("update CUSTOMER set C_PS = '"+I_PS +"' where C_ID = '" + C_ID +"'");
				rs = stmt.executeQuery("update CUSTOMER set C_NAME = '"+I_Name +"' where C_ID = '" + C_ID +"'");
				rs = stmt.executeQuery("update CUSTOMER set C_AGE = '"+I_Age +"' where C_ID = '" + C_ID +"'");
				rs = stmt.executeQuery("update CUSTOMER set C_GENDER = '"+I_Gender +"' where C_ID = '" + C_ID +"'");
				rs = stmt.executeQuery("update CUSTOMER set C_ADDRESS = '"+I_Address +"' where C_ID = '" + C_ID +"'");
				rs = stmt.executeQuery("update CUSTOMER set C_PHONENUMBER = '"+I_Phone +"' where C_ID = '" + C_ID +"'");
				rs = stmt.executeQuery("update CUSTOMER set C_RANK = '"+I_Rank +"' where C_ID = '" + C_ID +"'");
				rs = stmt.executeQuery("update CUSTOMER set C_MILEAGE = '"+I_Mileage +"' where C_ID = '" + C_ID +"'");
			 rs.close();
			stmt.close();
			conn.close();
			
	}
	catch(Exception e) {
		e.printStackTrace();
	}
		
		
		
		
		
		%>
		
		<form action="EmployeeMain.jsp" method="POST">
		<input type="hidden" name="ID" value="<%=ID%>">
		<input type="submit" value="HOME">
</form>
</body>
</html>