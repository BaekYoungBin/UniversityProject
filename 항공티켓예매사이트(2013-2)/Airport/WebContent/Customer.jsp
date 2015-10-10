<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>개인정보 수정</title>
</head>
<body>
	<%@ page import="java.io.*"%>
	<%@ page import="java.sql.*"%>
	<%
	String tmpID = request.getParameter("ID");
	String C_ID = "null";
	String C_PS = "null";
	String C_Name = "null";
	String C_Age = "null";
	String C_Gender = "null";
	String C_Address = "null";
	String C_Phone = "null";
	String C_Rank = "null";
	String C_Mileage = "null";
	String DB_URL = "jdbc:oracle:thin:@165.132.221.101:1521:XE";
	try{
			DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
			Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@165.132.221.101:1521:XE","db09253072","ghk2xld");
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery("select * from CUSTOMER where C_ID = '" + tmpID +"'");			
		while(rs.next())
		{
			C_ID = rs.getString("C_ID");
			C_PS = rs.getString("C_PS");
			C_Name = new String(rs.getString("C_NAME").getBytes("8859_1"));	
			C_Age = rs.getString("C_AGE");
			C_Gender = rs.getString("C_GENDER");
			C_Address = new String(rs.getString("C_ADDRESS").getBytes("8859_1"));	
			C_Phone = rs.getString("C_PHONENUMBER");
			C_Rank = rs.getString("C_RANK");
			C_Mileage = rs.getString("C_MILEAGE");
			
		}	
		%>
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
				<td><%=C_ID %></td>
				<td><%=C_PS %></td>
				<td><%=C_Name %></td>
				<td><%=C_Age %></td>
				<td><%=C_Gender %></td>
				<td><%=C_Address %></td>
				<td><%=C_Phone %></td>
				<td><%=C_Rank %></td>
				<td><%=C_Mileage %></td>
				</tr>
				
				<%
		
		
		rs.close();
		stmt.close();
		conn.close();
	}
		
	catch(Exception e) {
		e.printStackTrace();
	}
		
		
		
		
		%>
		</table>
		<form action="CustomerInsert.jsp" method="POST" >
		<input type="hidden" name="ID" value="<%=C_ID%>">
		<input type="submit" value="수정">
		
		</form>
	
		<form action="Customer_Report.jsp" method="POST" >
		<input type="submit" value="탑승내역">
		<input type="hidden" name="ID" value="<%=C_ID%>">
			</form>
		<input type="button" value="뒤로" onclick="history.go(-1)">		
		
</body>
</html>