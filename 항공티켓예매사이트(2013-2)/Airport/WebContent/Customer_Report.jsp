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
	out.print(ID);
	String DB_URL = "jdbc:oracle:thin:@165.132.221.101:1521:XE";	
	%>
	<table border='1'  bordercolor = '#AE52IC'>
	<tr>
	<th>ID</th><th>비행기종</th><th>출발지</th><th>도착지</th>
	</tr>
	<%
	String TotalCost;
	int TotalCostInt= 0;
	String C_ID = "null";
	String Plane_Type = "null";
	String Origin = "null";
	try{
		DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
		Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@165.132.221.101:1521:XE","db09253072","ghk2xld");
		Statement stmt = conn.createStatement();
		ResultSet rs = stmt.executeQuery("select C_ID, Plane_type, Origin, Destination from customer_Boarding_Report where c_id = '"+ID+"'");
		while (rs.next()){		
			C_ID = rs.getString("C_ID");
			Plane_Type = rs.getString("Plane_Type");
			Origin = rs.getString("Origin");
			String Destination = rs.getString("Destination");
			
			%>	
			<tr><td><%=C_ID %></td><td><%=Plane_Type%></td><td><%=Origin%></td><td><%=Destination%></td>
			<%
	
		}

		rs.close();
		stmt.close();
		conn.close();
	}
	catch (Exception e){
		out.println("Error");
		e.printStackTrace();
	}
	
	
	
	%>
	
	
</table>	
	
	
	<input type = "button" value = "뒤로가기"  onclick = "history.go(-1)">
<form action="CustomerMain.jsp" method="POST">
<input type="hidden" name="ID" value="<%=ID%>">
<input type="submit" value="HOME">
</form>
	<form action="Login.jsp" method="POST" >
	<input type="submit" value="Logout">
	</form>
</body>
</html>