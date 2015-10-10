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
	<%String tmpID = request.getParameter("tmpID");
	String tmpPassword = request.getParameter("tmpPassword"); %>
	<% 
	String ID = request.getParameter("ID");
	String pwd = request.getParameter("pwd");
	String pwd_conf = request.getParameter("pwd_conf");
	String name = request.getParameter("name");
	String age = request.getParameter("age");
	String gender = request.getParameter("gender");
	String address = request.getParameter("address");
	String phone = request.getParameter("phone");
%>
	<%
		int validate = 1;
		String DB_URL = "jdbc:oracle:thin:@165.132.221.101:1521:XE";
		try{
			Class.forName("oracle.jdbc.driver.OracleDriver");
			Connection con = DriverManager.getConnection(DB_URL,"db09253072", "ghk2xld");
			Statement stmt = con.createStatement();
			// ID duplicate check
			ResultSet rs0 = stmt.executeQuery("select c_ID from customer where c_id='" + ID + "'");
			if (rs0.next()) {
				out.print("Duplicated ID");
				validate = 0;
			}
			// validate check
			if (ID.length() > 21 || ID.length() < 1) {
				out.print("Too long or short ID");
				validate = 0;
			} 
			if (pwd.length() > 18 || pwd.length() < 4) {
				out.print("Too long or short password");
				validate = 0;
			}
			if (!pwd.equals(pwd_conf)) {
				out.print("mismatch password");
				validate = 0;
			}
			if (name.length() > 18 || name.length() < 1) {
				out.print("Too long or short name");
				validate = 0;
			}
			if (validate == 1) {
				ResultSet rs = stmt
						.executeQuery("insert into customer values(" + "'"
								+ ID + "'," + "'" + pwd + "'," + "'" + name
								+ "', " + "'" + age +"'," + "'" + gender+"'," + "'"+address +"',"+"'" + phone +"'," +"'0', '0')" );
				rs.close();
				out.print("Welcome!");
				%> <br> <br> <form action="Login.jsp" method="POST">
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