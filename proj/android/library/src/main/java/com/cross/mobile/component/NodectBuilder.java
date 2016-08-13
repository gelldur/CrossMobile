package com.cross.mobile.component;

import android.support.annotation.Keep;

import java.util.ArrayList;

/**
 * Created by Dawid Drozd aka Gelldur on 8/10/16.
 */

/**
 * Class is used to build Nodect on native side
 */
@Keep
public class NodectBuilder {

	public NodectBuilder(String tag, Object context) {
		_tag = tag;
		_context = context;
	}

	public NodectBuilder nest(NodectBuilder nodectBuilder) {
		if (_nested == null) {
			_nested = new ArrayList<>(4);
		}
		_nested.add(nodectBuilder);
		return this;
	}

	public NodectBuilder addComponent(String component) {
		if (_components == null) {
			_components = new ArrayList<>(4);
		}
		_components.add(component);
		return this;
	}

	@SuppressWarnings("unused") //Used in JNI
	@Keep
	public String getTag() {
		return _tag;
	}

	@SuppressWarnings("unused") //Used in JNI
	@Keep
	public Object getContext() {
		return _context;
	}

	@SuppressWarnings("unused") //Used in JNI
	@Keep
	public String getComponent(int index) {
		return _components.get(index);
	}

	@SuppressWarnings("unused") //Used in JNI
	@Keep
	public int getComponentCount() {
		if (_components == null) {
			return 0;
		}
		return _components.size();
	}

	@SuppressWarnings("unused") //Used in JNI
	@Keep
	public NodectBuilder getNested(int index) {
		return _nested.get(index);
	}

	@SuppressWarnings("unused") //Used in JNI
	@Keep
	public int getNestedCount() {
		if (_nested == null) {
			return 0;
		}
		return _nested.size();
	}

	private final String _tag;
	private final Object _context;
	private ArrayList<String> _components;
	private ArrayList<NodectBuilder> _nested;
}
