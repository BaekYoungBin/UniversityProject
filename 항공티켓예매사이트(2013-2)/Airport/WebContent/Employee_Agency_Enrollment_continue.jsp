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
	String A_ID = request.getParameter("A_ID");
	String pwd = request.getParameter("pwd");
	String pwd_conf = request.getParameter("pwd_conf");
	String A_Name = request.getParameter("A_Name");
	String A_address = request.getParameter("A_address");
	String A_phone = request.getParameter("A_phone");
	
%>
	<%
		int validate = 1;
		String DB_URL = "jdbc:oracle:thin:@165.132.221.101:1521:XE";
		try{
			Class.forName("oracle.jdbc.driver.OracleDriver");
			Connection con = DriverManager.getConnection(DB_URL,"db09253072", "ghk2xld");
			Statement stmt = con.createStatement();
			// ID duplicate check
			ResultSet rs0 = stmt.executeQuery("select A_ID from Agency where A_ID='" + A_ID + "'");
			if (rs0.next()) {
				out.print("Duplicated ID");
				validate = 0;
			}
			// validate check
			if (A_ID.length() > 11 || A_ID.length() < 1) {
				out.print("Too long or short ID");
				validate = 0;
			} 
			if (pwd.length() > 20 || pwd.length() < 4) {
				out.print("Too long or short password");
				validate = 0;
			}
			if (!pwd.equals(pwd_conf)) {
				out.print("mismatch password");
				validate = 0;
			}
			if (A_Name.length() > 20 || A_Name.length() < 1) {
				out.print("Too long or short name");
				validate = 0;
			}
			if (A_address.length() > 60 || A_address.length() < 1) {
				out.print("Too long or short name");
				validate = 0;
			}
			if (A_phone.length() > 20 || A_phone.length() < 1) {
				out.print("Too long or short name");
				validate = 0;
			}
			if (validate == 1) {
				ResultSet rs = stmt
						.executeQuery("insert into Agency values(" + "'"
								+ A_ID + "'," + "'" + pwd + "'," + "'" + A_Name
								+ "', " + "'" + A_address +"'," + "'" + A_phone+ "')" );
				rs.close();
				out.print("Agency Enrollment Success!");
				%> <br> <br> 
	                <form action="EmployeeMain.jsp" method="POST">
<input type="hidden" name="ID" value="<%=ID%>">
<input type="submit" value="HOME">
</form>         
	 <%
			}
			else
				%> <br> <br> <input type="button" value="Back" onclick="history.go(-1)"> <%
			stmt.close();
			con.close();
			
		} catch (Exception e) {
			out.println("ERROR");
			e.printStackTrace();
		}
	%>
</body>
</html>