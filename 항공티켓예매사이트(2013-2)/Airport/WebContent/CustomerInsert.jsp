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
	String tmpID = request.getParameter("ID");
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
			C_Gender = rs.getString("C_GENDER");
			C_Rank = rs.getString("C_RANK");
			C_Mileage = rs.getString("C_MILEAGE");
			
		}	
		%>
		<form  action = "CustomerInsert_continue.jsp" method = "POST">
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
				
				<td> <%=tmpID %></td>
				
				<td> <input type = "password" name = "PS" style ="width:80px; height = 20px;"/></td>
				<td> <input type = "text" name = "Name" style ="width:50px; height = 20px;"/></td>
				<td> <input type = "text" name = "Age" style ="width:30px; height = 20px;"/></td>
				<td> <%=C_Gender %></td>
				<td> <input type = "text" name = "Address" style ="width:160px; height = 20px;"/></td>
				<td> <input type = "text" name = "Phone" style ="width:100px; height = 20px;"/></td>
				<td><%=C_Rank %></td>
				<td><%=C_Mileage %></td>
				</tr>
				</table>
			<input type="hidden" name="ID" value="<%=tmpID%>">
			<input type = "submit" value = "저장"><input type="reset">
			<input type="button" value="취소" onclick="history.go(-1)">				
			</form>
				
		<%
		
		rs.close();
		stmt.close();
		conn.close();
	}
		
	catch(Exception e) {
		e.printStackTrace();
	}
		
		
		
		
		%>

</body>
</html>