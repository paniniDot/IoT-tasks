/*
 * This file was generated by the Gradle 'init' task.
 *
 * This generated file contains a sample Java application project to get you started.
 * For more details take a look at the 'Building Java & JVM projects' chapter in the Gradle
 * User Manual available at https://docs.gradle.org/8.0.1/userguide/building_java_projects.html
 */

plugins {
    // Apply the application plugin to add support for building a CLI application in Java.
    application
}

repositories {
    // Use Maven Central for resolving dependencies.
    mavenCentral()
}

dependencies {
    // Use JUnit Jupiter for testing.
    testImplementation("org.junit.jupiter:junit-jupiter:5.9.1")

    // This dependency is used by the application.
    implementation("com.google.guava:guava:31.1-jre")
    
    // https://mvnrepository.com/artifact/org.eclipse.paho/org.eclipse.paho.client.mqttv3
    implementation("org.eclipse.paho:org.eclipse.paho.client.mqttv3:1.2.5")
    
    // https://mvnrepository.com/artifact/io.github.java-native/jssc
	implementation("io.github.java-native:jssc:2.9.4")
	
	// https://mvnrepository.com/artifact/org.slf4j/slf4j-api
	implementation("org.slf4j:slf4j-api:2.0.6")
	
	// https://mvnrepository.com/artifact/org.apache.logging.log4j/log4j-slf4j2-impl
	implementation("org.apache.logging.log4j:log4j-slf4j2-impl:2.20.0")	

    // https://central.sonatype.com/artifact/io.vertx/vertx-core/4.4.3
    implementation("io.vertx:vertx-core:4.2.6")
    implementation("io.vertx:vertx-web:4.2.6")
    implementation("io.vertx:vertx-web-client:4.2.6")

    implementation("com.google.code.gson:gson:2.10.1")
}

application {
    // Define the main class for the application.
    mainClass.set("room.service.App")
}

tasks.named<Test>("test") {
    // Use JUnit Platform for unit tests.
    useJUnitPlatform()
}
